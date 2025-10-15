#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace tinyredis {

/**
 * Thread-unsafe in-memory storage for Redis-style data structures.
 *
 * NOTE: The goal of this skeleton is to outline the moving parts.
 *       Actual behaviour is intentionally left as TODOs for you.
 */
class DataStore {
public:
    using Value = std::vector<std::string>;

    DataStore() = default;
    ~DataStore() = default;

    DataStore(const DataStore&) = delete;
    DataStore& operator=(const DataStore&) = delete;

    DataStore(DataStore&&) noexcept = default;
    DataStore& operator=(DataStore&&) noexcept = default;

    std::optional<Value> get(const std::string& key) const;
    void set(const std::string& key, Value value);
    bool del(const std::string& key);

private:
    std::unordered_map<std::string, Value> storage_;

    // TODO: Add expiry bookkeeping for keys (e.g. std::unordered_map<std::string, std::chrono::steady_clock::time_point>)
};

}  // namespace tinyredis
