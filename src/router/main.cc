#include <iostream>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "src/common/protocol.h"

using namespace herodb;

struct Backend {
    std::string host;
    int port;
};

std::vector<Backend> g_backends;

int get_backend_index(const std::string& key) {
    size_t hash = std::hash<std::string>{}(key);
    return hash % g_backends.size();
}

void forward_request(int client_fd) {
    json request;
    while (receive_json(client_fd, request)) {
        std::string shard_key;
        if (request["op"] == "insert") {
            shard_key = request["doc"].value("_id", "");
        } else {
            shard_key = request.value("_id", "");
        }

        int idx = 0;
        if (!shard_key.empty()) {
            idx = get_backend_index(shard_key);
        }

        // Connect to backend
        int back_fd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(g_backends[idx].port);
        inet_pton(AF_INET, g_backends[idx].host.c_str(), &serv_addr.sin_addr);

        if (connect(back_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            json resp;
            resp["status"] = "error";
            resp["message"] = "backend connection failed";
            send_json(client_fd, resp);
            close(back_fd);
            continue;
        }

        send_json(back_fd, request);
        json response;
        receive_json(back_fd, response);
        send_json(client_fd, response);
        close(back_fd);
    }
    close(client_fd);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <listen_port> <backend1_host:port> <backend2_host:port> ..." << std::endl;
        return 1;
    }

    int listen_port = std::stoi(argv[1]);
    for (int i = 2; i < argc; ++i) {
        std::string s = argv[i];
        size_t colon = s.find(':');
        g_backends.push_back({s.substr(0, colon), std::stoi(s.substr(colon + 1))});
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(listen_port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }
    listen(server_fd, 3);

    std::cout << "HeroDB Router (Death Legion Team) started on port " << listen_port << std::endl;
    std::cout << "Routing to " << g_backends.size() << " backends" << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) continue;
        std::thread(forward_request, client_fd).detach();
    }

    return 0;
}
