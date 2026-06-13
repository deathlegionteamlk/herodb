#include <iostream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include "src/common/protocol.h"
#include "src/server/storage.h"

using namespace herodb;

Storage g_storage;

void handle_client(int client_fd) {
    json request;
    while (receive_json(client_fd, request)) {
        std::string op = request.value("op", "");
        json response;
        
        if (op == "insert") {
            json doc = request["doc"];
            std::string id = doc.value("_id", "");
            if (id.empty()) {
                id = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
                doc["_id"] = id;
            }
            g_storage.insert(id, doc);
            response["status"] = "ok";
            response["_id"] = id;
        } else if (op == "find") {
            std::string id = request.value("_id", "");
            if (!id.empty()) {
                json doc = g_storage.find(id);
                if (!doc.is_null()) {
                    response["status"] = "ok";
                    response["doc"] = doc;
                } else {
                    response["status"] = "not_found";
                }
            } else {
                response["status"] = "ok";
                response["docs"] = g_storage.find_all();
            }
        } else if (op == "delete") {
            std::string id = request.value("_id", "");
            if (g_storage.remove(id)) {
                response["status"] = "ok";
            } else {
                response["status"] = "not_found";
            }
        } else {
            response["status"] = "error";
            response["message"] = "unknown operation";
        }
        
        if (!send_json(client_fd, response)) break;
    }
    close(client_fd);
}

int main(int argc, char** argv) {
    int port = 8080;
    if (argc > 1) port = std::stoi(argv[1]);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }
    listen(server_fd, 3);

    std::cout << "HeroDB Server (Death Legion Team) started on port " << port << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) continue;
        std::thread(handle_client, client_fd).detach();
    }

    return 0;
}
