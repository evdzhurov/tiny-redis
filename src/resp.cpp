#include "tinyredis/resp.hpp"

#include <stdexcept>

namespace tinyredis
{

    RespMessage parse_resp_message(const std::vector<char>& buffer, std::size_t& offset)
    {
        // TODO: Implement RESP parsing state machine supporting arrays, bulk strings, integers,
        // simple strings and errors.
        (void)buffer;
        (void)offset;
        throw std::logic_error("parse_resp_message() is not yet implemented");
    }

    std::vector<char> serialize_resp_message(const RespMessage& message)
    {
        // TODO: Implement RESP serialization matching parse_resp_message() output.
        (void)message;
        throw std::logic_error("serialize_resp_message() is not yet implemented");
    }

    std::string message_type_to_string(const RespMessage& message)
    {
        // TODO: Provide helpful name for logging/metrics based on RESP variant.
        (void)message;
        return "unimplemented";
    }

} // namespace tinyredis
