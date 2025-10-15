#include "tinyredis/datastore.hpp"

#include <algorithm>

namespace tinyredis {

std::optional<DataStore::Value> DataStore::get(const std::string& key) const {
    const auto it = storage_.find(key);
    if (it == storage_.end()) {
        return std::nullopt;
    }

    // TODO: Respect expiry metadata so keys past TTL return null.
    return it->second;
}

void DataStore::set(const std::string& key, Value value) {
    // TODO: Support NX/XX modifiers and expiry updates.
    storage_[key] = std::move(value);
}

bool DataStore::del(const std::string& key) {
    // TODO: Support deleting multiple keys at once (DEL k1 k2 ...).
    return storage_.erase(key) > 0;
}

}  // namespace tinyredis
