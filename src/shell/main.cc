#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "src/common/protocol.h"

using namespace herodb;

void print_help() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  insert <json_doc>  - Insert a document" << std::endl;
    std::cout << "  find <id>          - Find a document by ID" << std::endl;
    std::cout << "  find               - Find all documents" << std::endl;
    std::cout << "  delete <id>        - Delete a document by ID" << std::endl;
    std::cout << "  exit               - Exit the shell" << std::endl;
}

int main(int argc, char** argv) {
    std::string host = "127.0.0.1";
    int port = 8080;
    if (argc > 1) host = argv[1];
    if (argc > 2) port = std::stoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed to " << host << ":" << port << std::endl;
        return 1;
    }

    std::cout << "Connected to HeroDB (Death Legion Team) at " << host << ":" << port << std::endl;
    print_help();

    std::string line;
    while (std::cout << "herodb> " && std::getline(std::cin, line)) {
        if (line == "exit") break;
        if (line.empty()) continue;

        size_t space = line.find(' ');
        std::string cmd = line.substr(0, space);
        json request;
        
        if (cmd == "insert") {
            if (space == std::string::npos) {
                std::cout << "Usage: insert <json_doc>" << std::endl;
                continue;
            }
            try {
                request["op"] = "insert";
                request["doc"] = json::parse(line.substr(space + 1));
            } catch (...) {
                std::cout << "Invalid JSON" << std::endl;
                continue;
            }
        } else if (cmd == "find") {
            request["op"] = "find";
            if (space != std::string::npos) {
                request["_id"] = line.substr(space + 1);
            }
        } else if (cmd == "delete") {
            if (space == std::string::npos) {
                std::cout << "Usage: delete <id>" << std::endl;
                continue;
            }
            request["op"] = "delete";
            request["_id"] = line.substr(space + 1);
        } else {
            std::cout << "Unknown command" << std::endl;
            continue;
        }

        if (!send_json(sock, request)) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }

        json response;
        if (receive_json(sock, response)) {
            std::cout << response.dump(2) << std::endl;
        } else {
            std::cout << "Failed to receive response" << std::endl;
            break;
        }
    }

    close(sock);
    return 0;
}
