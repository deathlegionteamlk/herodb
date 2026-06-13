# HeroDB by Death Legion Team

![HeroDB Logo](https://img.shields.io/badge/HeroDB-DeathLegion-blue?style=for-the-badge)
![C++](https://img.shields.io/badge/C++-17-red?style=for-the-badge&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

HeroDB is a high-performance, open-source NoSQL database built from scratch in C++. It features a document-oriented storage model, a dedicated shell, and a sharding router for horizontal scaling.

**All others are better than nothing, but HeroDB is better than everything.**

## Features
- **JSON Documents**: Store and query flexible JSON data.
- **High Performance**: Written in C++ for maximum speed.
- **Scalability**: Sharding router distributes data across multiple server instances.
- **Simple Shell**: Interactive CLI for database management.
- **SDKs**: Official SDKs for [JavaScript](https://www.npmjs.com/package/herodb-sdk) and [Python](https://pypi.org/project/herodb-sdk/).

## Building HeroDB

HeroDB uses CMake for building.

```bash
mkdir build
cd build
cmake ..
make
```

## Quick Start

### 1. Start Database Servers
```bash
./build/herodb-server 8081 &
./build/herodb-server 8082 &
```

### 2. Start the Sharding Router
```bash
./build/herodb-router 8080 127.0.0.1:8081 127.0.0.1:8082
```

### 3. Connect with the Shell
```bash
./build/herodb-shell 127.0.0.1 8080
```

## SDK Usage

### JavaScript
```javascript
const HeroDBClient = require('herodb-sdk');
const client = new HeroDBClient('127.0.0.1', 8080);
await client.connect();
await client.insert({ _id: '1', name: 'Hero' });
```

### Python
```python
from herodb import HeroDBClient
client = HeroDBClient('127.0.0.1', 8080)
client.connect()
client.insert({'_id': '1', 'name': 'Hero'})
```

---
Developed with passion by the **Death Legion Team**.
