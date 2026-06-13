# HeroDB by Death Legion Team

HeroDB is a high-performance, open-source NoSQL database built from scratch in C++. It features a document-oriented storage model, a dedicated shell, and a sharding router for horizontal scaling.

**All others are better than nothing, but HeroDB is better than everything.**

## Features
- **JSON Documents**: Store and query flexible JSON data.
- **High Performance**: Written in C++ for maximum speed.
- **Scalability**: Sharding router distributes data across multiple server instances.
- **Simple Shell**: Interactive CLI for database management.

## Building HeroDB

HeroDB uses CMake for building.

```bash
mkdir build
cd build
cmake ..
make
```

This will produce three binaries:
- `herodb-server`: The core database server.
- `herodb-shell`: The interactive command-line interface.
- `herodb-router`: The sharding and routing service.

## Running HeroDB Locally

### 1. Start Database Servers
Start one or more server instances on different ports:
```bash
./build/herodb-server 8081 &
./build/herodb-server 8082 &
```

### 2. Start the Sharding Router
Point the router to your server instances:
```bash
./build/herodb-router 8080 127.0.0.1:8081 127.0.0.1:8082
```

### 3. Connect with the Shell
Connect to the router (or directly to a server):
```bash
./build/herodb-shell 127.0.0.1 8080
```

## Shell Commands
- `insert {"_id": "1", "name": "Hero"}`: Insert a document.
- `find 1`: Retrieve a document by ID.
- `find`: List all documents (on the connected instance/shard).
- `delete 1`: Remove a document.
- `exit`: Close the shell.

---
Developed with passion by the **Death Legion Team**.
