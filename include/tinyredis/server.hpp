#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "tinyredis/command_router.hpp"
#include "tinyredis/datastore.hpp"
#include "tinyredis/resp.hpp"

namespace tinyredis {

struct ClientState {
    int fd{-1};
    std::vector<char> input_buffer{};
    std::vector<char> output_buffer{};
    RespMessage in_progress{};

    // TODO: Track partial RESP parsing progress and pending commands.
};

struct ServerConfig {
    std::string host{"127.0.0.1"};
    std::uint16_t port{6379};
    int backlog{128};
    int epoll_max_events{64};
    bool verbose_logging{false};

    // TODO: Add configuration for timeouts and persistence (AOF/RDB).
};

class Server {
public:
    explicit Server(ServerConfig config);
    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void run();

private:
    void setup_listener();
    void main_loop();
    void accept_connection();
    void handle_readable(int fd);
    void handle_writable(int fd);
    void close_connection(int fd);
    void process_client_buffer(ClientState& client);

    ServerConfig config_;
    int listen_fd_{-1};
    int epoll_fd_{-1};
    std::unordered_map<int, ClientState> clients_;
    DataStore store_;
    CommandRouter router_;
};

}  // namespace tinyredis
