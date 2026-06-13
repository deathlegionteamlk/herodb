<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,4&height=220&section=header&text=HeroDB&fontSize=85&fontColor=ff3333&fontAlignY=38&desc=C%2B%2B%20NoSQL%20database.%20No%20GC.%20No%20fluff.&descAlignY=60&descSize=20&animation=fadeIn" width="100%"/>

<br/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=20&duration=2500&pause=800&color=FF3333&center=true&vCenter=true&multiline=true&width=640&height=80&lines=Native+C%2B%2B.+Talks+to+hardware+directly.;Shard+across+thousands+of+nodes.;JS+%26+Python+SDKs+included." alt="Typing animation" />

<br/><br/>

[![GitHub Release](https://img.shields.io/github/v/release/deathlegionteamlk/herodb?style=for-the-badge&logo=github&logoColor=white&color=1a1a1a)](https://github.com/deathlegionteamlk/herodb/releases)
[![npm](https://img.shields.io/npm/v/herodb-sdk?style=for-the-badge&logo=npm&logoColor=white&color=cc3333)](https://www.npmjs.com/package/herodb-sdk)
[![PyPI](https://img.shields.io/pypi/v/herodb-sdk?style=for-the-badge&logo=python&logoColor=white&color=991111)](https://pypi.org/project/herodb-sdk/)
[![Built by](https://img.shields.io/badge/💀-Death%20Legion%20Team-1a1a1a?style=for-the-badge)](https://github.com/deathlegionteamlk)

</div>

---

## 💀 What is HeroDB?

Most databases are written in languages that manage memory for you. That's convenient, but you pay for it — pauses, overhead, latency spikes at the worst possible moment.

HeroDB is written in C++. It talks to the hardware directly. There's no garbage collector running in the background, no runtime doing bookkeeping between your query and your disk. You write data. It writes data.

It's a document database — NoSQL, schema-flexible — with a sharding layer built in from the start, not bolted on later.

<div align="center">
<img src="https://user-images.githubusercontent.com/74038190/212284100-561aa473-3905-4a80-b561-0d28506553ee.gif" width="600"/>
</div>

---

## ⚡ Why C++?

<div align="center">
<img src="https://user-images.githubusercontent.com/74038190/212257468-1e9a91f1-b626-4baa-b15d-5c385dfa7ed2.gif" width="80"/>
</div>

The short version: managed runtimes have a cost. Java, Go, Python — they all do something between you and the metal. For most workloads that's fine. For a database handling millions of ops/sec, those microseconds add up.

HeroDB skips all of that. Manual memory management, no GC pauses, direct I/O — the kind of control you need when latency is the whole game.

---

## 📦 Ecosystem

<table>
<tr>
<td width="25%" align="center">

### 🔴 Core Server
High-performance C++ engine

[↓ Download](https://github.com/deathlegionteamlk/herodb/releases)

</td>
<td width="25%" align="center">

### 🔀 Sharding Router
Horizontal scaling layer

[↓ Download](https://github.com/deathlegionteamlk/herodb/releases)

</td>
<td width="25%" align="center">

### 🟨 JS SDK
Node.js client

```bash
npm install herodb-sdk
```

</td>
<td width="25%" align="center">

### 🐍 Python SDK
Python client

```bash
pip install herodb-sdk
```

</td>
</tr>
</table>

---

## 🚀 Quickstart

<div align="center">
<img src="https://user-images.githubusercontent.com/74038190/212257454-16e3712e-945a-4ca2-b238-408ad0bf87e6.gif" width="80"/>
</div>

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

## 🔀 Horizontal Scaling

<div align="center">
<img src="https://user-images.githubusercontent.com/74038190/229223263-cf2e4b07-2615-4f87-9c38-e37600f8381a.gif" width="380"/>
</div>

Sharding is built in, not an afterthought. Start as many `herodb-server` instances as you need, then point a `herodb-router` at all of them. The router handles distribution — your application just talks to one endpoint.

```bash
# Boot the router against three backend shards
./herodb-router 8080 10.0.0.1:8081 10.0.0.2:8081 10.0.0.3:8081
```

```
┌──────────────────────────────────────────────────┐
│                 Your Application                 │
└─────────────────────┬────────────────────────────┘
                      │
              ┌───────▼────────┐
              │  herodb-router  │  :8080
              │  (distributes) │
              └──┬──────┬──────┘
                 │      │      │
        ┌────────▼─┐ ┌──▼─────┐ ┌▼────────┐
        │  shard 1 │ │ shard 2│ │ shard 3 │
        │ :8081    │ │ :8081  │ │ :8081   │
        └──────────┘ └────────┘ └─────────┘
```

Add more shards, point the router at them, done. No resharding ceremony, no downtime required.

---

## 🛡️ License

MIT © [Death Legion Team](https://github.com/deathlegionteamlk)

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=0,2,4&height=100&section=footer&animation=fadeIn" width="100%"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=13&duration=4000&pause=1000&color=FF3333&center=true&vCenter=true&width=500&lines=C%2B%2B.+Direct+hardware+access.+No+GC.;Shard+it.+Scale+it.+Ship+it.;💀+Built+with+Death+Legion+Team." alt="Footer typing" />

</div>
