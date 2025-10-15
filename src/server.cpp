#include "tinyredis/server.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

namespace tinyredis {

Server::Server(ServerConfig config)
    : config_(std::move(config)), router_() {
    // TODO: Initialise logging sinks, signal handlers, and persistence layer.
}

Server::~Server() {
    // TODO: Close sockets and flush persistence buffers safely.
}

void Server::run() {
    setup_listener();
    main_loop();
}

void Server::setup_listener() {
    // TODO: Create non-blocking TCP socket, configure reuse flags, bind, listen, and register with epoll/kqueue.
    throw std::logic_error("setup_listener() is not yet implemented");
}

void Server::main_loop() {
    // TODO: Implement edge-triggered epoll (or select/poll) event loop.
    throw std::logic_error("main_loop() is not yet implemented");
}

void Server::accept_connection() {
    // TODO: Accept new clients, set sockets non-blocking, and add to epoll interest list.
    throw std::logic_error("accept_connection() is not yet implemented");
}

void Server::handle_readable(int fd) {
    // TODO: Read bytes into per-client buffer and parse RESP messages incrementally.
    (void)fd;
    throw std::logic_error("handle_readable() is not yet implemented");
}

void Server::handle_writable(int fd) {
    // TODO: Flush pending RESP responses back to the client socket.
    (void)fd;
    throw std::logic_error("handle_writable() is not yet implemented");
}

void Server::close_connection(int fd) {
    // TODO: Ensure the socket is deregistered from epoll and closed.
    clients_.erase(fd);
    (void)fd;
}

void Server::process_client_buffer(ClientState& client) {
    // TODO: Convert buffered RESP frames into command arrays and dispatch to router_.
    (void)client;
}

}  // namespace tinyredis
