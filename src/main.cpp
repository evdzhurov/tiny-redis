#include <exception>
#include <iostream>

#include "tinyredis/server.hpp"

int main(int argc, char** argv) {
    using namespace tinyredis;

    ServerConfig config{};
    (void)argc;
    (void)argv;

    // TODO: Parse CLI flags (e.g. --port, --bind, --verbosity) into config.

    try {
        Server server{config};
        server.run();
    } catch (const std::exception& ex) {
        std::cerr << "[TinyRedis] fatal error: " << ex.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "[TinyRedis] fatal error: unknown exception\n";
        return 2;
    }

    return 0;
}
