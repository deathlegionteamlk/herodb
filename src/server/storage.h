#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include "third_party/json.hpp"

namespace herodb {

class Storage {
public:
    using json = nlohmann::json;

    void insert(const std::string& id, const json& doc) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_[id] = doc;
    }

    json find(const std::string& id) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_.find(id) != data_.end()) {
            return data_[id];
        }
        return nullptr;
    }

    bool remove(const std::string& id) {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_.erase(id) > 0;
    }

    json find_all() {
        std::lock_guard<std::mutex> lock(mutex_);
        json res = json::array();
        for (const auto& [id, doc] : data_) {
            res.push_back(doc);
        }
        return res;
    }

private:
    std::unordered_map<std::string, json> data_;
    std::mutex mutex_;
};

} // namespace herodb
