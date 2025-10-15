#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace tinyredis {

struct RespSimpleString {
    std::string value;
};

struct RespBulkString {
    std::optional<std::string> value;
};

struct RespError {
    std::string value;
};

struct RespInteger {
    std::int64_t value;
};

struct RespArray;

using RespMessage = std::variant<
    RespSimpleString,
    RespBulkString,
    RespError,
    RespInteger,
    std::monostate,  // placeholder for RESP Null
    std::shared_ptr<RespArray>
>;

struct RespArray {
    std::vector<RespMessage> elements;
};

RespMessage parse_resp_message(const std::vector<char>& buffer, std::size_t& offset);
std::vector<char> serialize_resp_message(const RespMessage& message);
std::string message_type_to_string(const RespMessage& message);

// TODO: Add helper utilities for RESP3 if you want to extend protocol coverage.

}  // namespace tinyredis
