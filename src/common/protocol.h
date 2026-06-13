#pragma once

#include <string>
#include <vector>
#include "third_party/json.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

namespace herodb {

using json = nlohmann::json;

inline bool send_json(int fd, const json& j) {
    std::string s = j.dump();
    uint32_t len = htonl(s.size());
    if (send(fd, &len, sizeof(len), 0) != sizeof(len)) return false;
    if (send(fd, s.c_str(), s.size(), 0) != static_cast<ssize_t>(s.size())) return false;
    return true;
}

inline bool receive_json(int fd, json& j) {
    uint32_t len;
    ssize_t n = recv(fd, &len, sizeof(len), MSG_WAITALL);
    if (n <= 0) return false;
    len = ntohl(len);

    // Security: limit message size to 10MB to prevent OOM attacks
    if (len > 10 * 1024 * 1024) {
        return false;
    }
    
    std::vector<char> buffer(len);
    n = recv(fd, buffer.data(), len, MSG_WAITALL);
    if (n <= 0) return false;
    
    try {
        j = json::parse(buffer.begin(), buffer.end());
    } catch (...) {
        return false;
    }
    return true;
}

} // namespace herodb
