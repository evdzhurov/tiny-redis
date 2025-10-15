#pragma once

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "tinyredis/datastore.hpp"
#include "tinyredis/resp.hpp"

namespace tinyredis
{

    using CommandHandler = std::function<RespMessage(DataStore&, const RespArray&)>;

    class CommandRouter
    {
      public:
        CommandRouter();

        std::optional<CommandHandler> find_handler(const std::string& command) const;

      private:
        void register_default_handlers();
        RespMessage handle_ping(DataStore&, const RespArray&);
        RespMessage handle_echo(DataStore&, const RespArray&);
        RespMessage handle_set(DataStore&, const RespArray&);
        RespMessage handle_get(DataStore&, const RespArray&);
        RespMessage handle_del(DataStore&, const RespArray&);

        std::unordered_map<std::string, CommandHandler> handlers_;
    };

} // namespace tinyredis
