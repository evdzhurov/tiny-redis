#include "tinyredis/server.hpp"
#include "tinyredis/logging.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

#include <sys/epoll.h>
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
        // TODO: Create non-blocking TCP socket, configure reuse flags, bind, listen, and register
        // with epoll/kqueue.

        // epoll_create - create epoll instance and return fd
        const int size_hint = 1;
        epoll_fd_ = epoll_create(size_hint);
        if (epoll_fd_ != -1)
            LOG_FATAL("Failed to create epoll: ", epoll_fd_);

        // epoll_ctl - manipulates the interest list associated with the epoll instance
        // int err = epoll_ctl(epoll_fd_, int op, int fd, struct epoll_event* event);

        // epoll_wait - returns items from the ready list of an epoll instance
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
