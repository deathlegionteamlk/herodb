# 💀 HeroDB

![HeroDB Banner](https://raw.githubusercontent.com/deathlegionteamlk/herodb/main/banner.png)

[![GitHub Release](https://img.shields.io/github/v/release/deathlegionteamlk/herodb?style=for-the-badge)](https://github.com/deathlegionteamlk/herodb/releases)
[![npm version](https://img.shields.io/npm/v/herodb-sdk?style=for-the-badge)](https://www.npmjs.com/package/herodb-sdk)
[![PyPI version](https://img.shields.io/pypi/v/herodb-sdk?style=for-the-badge)](https://pypi.org/project/herodb-sdk/)

**HeroDB** is the world's most aggressive, high-performance NoSQL database. Built from the ground up in C++ for the **Death Legion Team**, it is designed to handle massive-scale document storage with zero latency and infinite sharding capabilities.

---

## 🔥 Why HeroDB?

- **Extreme Performance**: Native C++ implementation means we talk to the hardware directly. No garbage collection, no overhead.
- **Infinite Scaling**: Built-in Sharding Router allows you to distribute data across thousands of nodes seamlessly.
- **Developer First**: Clean, intuitive SDKs for JavaScript and Python.
- **Death Legion Grade**: Built for reliability in the most demanding environments.

---

## 📦 Ecosystem

| Component | Description | Install |
| :--- | :--- | :--- |
| **Core Server** | High-performance C++ Engine | [Download Releases](https://github.com/deathlegionteamlk/herodb/releases) |
| **Sharding Router** | Horizontal Scaling Layer | [Download Releases](https://github.com/deathlegionteamlk/herodb/releases) |
| **JS SDK** | Official Node.js Client | `npm install herodb-sdk` |
| **Python SDK** | Official Python Client | `pip install herodb-sdk` |

---

## 🚀 Quick Start (SDKs)

### JavaScript
```javascript
const HeroDBClient = require('herodb-sdk');
const client = new HeroDBClient('127.0.0.1', 8080);
await client.connect();
await client.insert({ name: 'Death Legion Warrior' });
```

### Python
```python
from herodb import HeroDBClient
client = HeroDBClient('127.0.0.1', 8080)
client.connect()
client.insert({'name': 'Death Legion Commander'})
```

---

## 🛠 Advanced Scaling

HeroDB is sharded by default. Deploy multiple `herodb-server` instances and point a `herodb-router` at them to unlock true horizontal scale.

```bash
# Start the router pointing to backend shards
./herodb-router 8080 10.0.0.1:8081 10.0.0.2:8081 10.0.0.3:8081
```

---

Developed with 💀 by the **Death Legion Team**.
