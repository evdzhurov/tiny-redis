#include "tinyredis/server.hpp"
#include "tinyredis/logging.hpp"

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
            LOG_FATAL("Failed to create listen socket!");

        int yes = 1;
        setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        // Bind to the listen address
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = 0; // TODO host address
        addr.sin_port = config_.port;

        int err = bind(listen_fd_, (sockaddr*)&addr, sizeof(addr));
        if (err == -1)
            LOG_FATAL("Failed to bind server address!");

        // Mark socket as 'passive', backlog is the maximum queue depth for pending connections
        err = listen(listen_fd_, config_.backlog);
        if (err == -1)
            LOG_FATAL("Failed to as listen socket!");

        // Create epoll instance
        const int size_hint = 1;
        epoll_fd_ = epoll_create(size_hint);
        if (epoll_fd_ != -1)
            LOG_FATAL("Failed to create epoll instance!");

        epoll_event ev{};
        ev.events = EPOLLIN;
        ev.data.fd = listen_fd_;

        err = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_fd_, &ev);
        if (err == -1)
            LOG_FATAL("Failed to add listen sock to epoll instance!");
    }

    void Server::main_loop()
    {
        // TODO: Implement edge-triggered epoll (or select/poll) event loop.
        throw std::logic_error("main_loop() is not yet implemented");
    }

    void Server::accept_connection()
    {
        // TODO: Accept new clients, set sockets non-blocking, and add to epoll interest list.
        throw std::logic_error("accept_connection() is not yet implemented");
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
        // TODO: Ensure the socket is deregistered from epoll and closed.
        clients_.erase(fd);
        (void)fd;
    }

    void Server::process_client_buffer(ClientState& client)
    {
        // TODO: Convert buffered RESP frames into command arrays and dispatch to router_.
        (void)client;
    }

} // namespace tinyredis
