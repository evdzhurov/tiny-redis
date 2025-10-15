#include "tinyredis/server.hpp"
#include "tinyredis/logging.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <cstddef>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

namespace tinyredis
{

    Server::Server(ServerConfig config) : config_(std::move(config)), router_()
    {
        // TODO: Initialise logging sinks, signal handlers, and persistence layer.
    }

    Server::~Server()
    {
        // TODO: Close sockets and flush persistence buffers safely.
        close(epoll_fd_);
    }

    void Server::run()
    {
        setup_listener();
        main_loop();
    }

    void Server::setup_listener()
    {
        // Create non-blocking listen TCP socket
        listen_fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (listen_fd_ == -1)
            LOG_FATAL("Failed to create listen socket! errno: ", errno);

        int yes = 1;
        setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        // Bind to the listen address
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(config_.port);
        inet_pton(AF_INET, config_.host.c_str(), &addr.sin_addr);

        int err = bind(listen_fd_, (sockaddr*)&addr, sizeof(addr));
        if (err == -1)
            LOG_FATAL("Failed to bind server address! errno: ", errno);

        // Mark socket as 'passive', backlog is the maximum queue depth for pending connections
        err = listen(listen_fd_, config_.backlog);
        if (err == -1)
            LOG_FATAL("Failed to as listen socket! errno: ", errno);

        // Create epoll instance
        epoll_fd_ = epoll_create1(0);
        if (epoll_fd_ == -1)
            LOG_FATAL("Failed to create epoll instance! errno: ", errno);

        epoll_event ev{};
        ev.events = EPOLLIN;
        ev.data.fd = listen_fd_;

        err = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_fd_, &ev);
        if (err == -1)
            LOG_FATAL("Failed to add listen sock to epoll instance! errno: ", errno);

        LOG_INFO("TinyRedis server listening on ", config_.host, ":", config_.port, " ...");
    }

    void Server::main_loop()
    {
        std::vector<epoll_event> events(config_.epoll_max_events);

        for (;;) {
            int n = epoll_wait(epoll_fd_, events.data(), config_.epoll_max_events, -1);
            for (int i = 0; i < n; ++i) {
                if (events[i].data.fd == listen_fd_) {
                    accept_connections();
                }
                else {
                    if (events[i].events & (EPOLLHUP | EPOLLERR)) {
                        close_connection(events[i].data.fd);
                    }
                    else if (events[i].events & EPOLLIN) {
                        char buf[1024];
                        ssize_t n = read(events[i].data.fd, buf, sizeof(buf));
                        if (n == 0) {
                            close_connection(events[i].data.fd);
                        }
                    }
                }
            }
        }
    }

    void Server::accept_connections()
    {
        for (;;) {
            sockaddr_in client_addr{};
            socklen_t addr_len = sizeof(client_addr);

            // Accept client connection
            auto client_fd = accept4(listen_fd_, (sockaddr*)&client_addr, &addr_len,
                                     SOCK_NONBLOCK | SOCK_CLOEXEC);

            if (client_fd < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;

                LOG_ERROR("Error accepting connection: ", errno);
                break; // TODO: Should this be 'continue'?
            }

            // Add client fd to epoll instance
            epoll_event client_ev{};
            client_ev.events = EPOLLIN;
            client_ev.data.fd = client_fd;
            epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, client_fd, &client_ev);

            clients_.emplace(client_fd, ClientState{client_fd});

            LOG_INFO("Client ", client_fd, " connected. Clients: ", clients_.size());
        }
    }

    void Server::handle_readable(int fd)
    {
        // TODO: Read bytes into per-client buffer and parse RESP messages incrementally.
        (void)fd;
        throw std::logic_error("handle_readable() is not yet implemented");
    }

    void Server::handle_writable(int fd)
    {
        // TODO: Flush pending RESP responses back to the client socket.
        (void)fd;
        throw std::logic_error("handle_writable() is not yet implemented");
    }

    void Server::close_connection(int fd)
    {
        int err = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr);
        if (err == -1)
            LOG_FATAL("Failed to remove client ", fd, " from epoll instance!");

        err = close(fd);
        if (err == -1)
            LOG_FATAL("Failed to close client ", fd);

        clients_.erase(fd);

        LOG_INFO("Closed connection ", fd, " Clients: ", clients_.size());
    }

    void Server::process_client_buffer(ClientState& client)
    {
        // TODO: Convert buffered RESP frames into command arrays and dispatch to router_.
        (void)client;
    }

} // namespace tinyredis
