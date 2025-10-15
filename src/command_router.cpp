#include "tinyredis/command_router.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace tinyredis
{

namespace
{

std::string normalize_command(const std::string& command)
{
    std::string upper = command;
    std::transform(upper.begin(), upper.end(), upper.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::toupper(ch)); });
    return upper;
}

} // namespace

CommandRouter::CommandRouter()
{
    register_default_handlers();
}

std::optional<CommandHandler> CommandRouter::find_handler(const std::string& command) const
{
    const auto normalized = normalize_command(command);
    const auto it = handlers_.find(normalized);
    if (it == handlers_.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void CommandRouter::register_default_handlers()
{
    handlers_.emplace("PING", [this](DataStore& store, const RespArray& args) { return handle_ping(store, args); });
    handlers_.emplace("ECHO", [this](DataStore& store, const RespArray& args) { return handle_echo(store, args); });
    handlers_.emplace("SET", [this](DataStore& store, const RespArray& args) { return handle_set(store, args); });
    handlers_.emplace("GET", [this](DataStore& store, const RespArray& args) { return handle_get(store, args); });
    handlers_.emplace("DEL", [this](DataStore& store, const RespArray& args) { return handle_del(store, args); });

    // TODO: Register additional commands (INCR, LPUSH, LRANGE, etc.).
}

RespMessage CommandRouter::handle_ping(DataStore&, const RespArray& args)
{
    // TODO: Return argument as bulk string when provided, otherwise "PONG".
    (void)args;
    return RespSimpleString{"PONG"};
}

RespMessage CommandRouter::handle_echo(DataStore&, const RespArray& args)
{
    // TODO: Validate arity and echo back the input as a bulk string.
    (void)args;
    return RespError{"ECHO not implemented"};
}

RespMessage CommandRouter::handle_set(DataStore& store, const RespArray& args)
{
    // TODO: Parse arguments (key, value, options) and persist in DataStore.
    (void)store;
    (void)args;
    return RespError{"SET not implemented"};
}

RespMessage CommandRouter::handle_get(DataStore& store, const RespArray& args)
{
    // TODO: Fetch key from DataStore and return bulk string or null.
    (void)store;
    (void)args;
    return RespBulkString{std::nullopt};
}

RespMessage CommandRouter::handle_del(DataStore& store, const RespArray& args)
{
    // TODO: Delete keys from DataStore and return integer count of removed keys.
    (void)store;
    (void)args;
    return RespInteger{0};
}

} // namespace tinyredis
