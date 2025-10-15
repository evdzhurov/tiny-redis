# TinyRedis Skeleton

This repository contains a C++17 skeleton for a tiny Redis clone. The goal is to guide you through implementing the core pieces of the Redis server while keeping the codebase approachable.

## Layout

- `src/main.cpp` – entry point that wires configuration and starts the server loop.
- `src/server.cpp` – networking, event loop, and request lifecycle coordination.
- `src/command_router.cpp` – dispatch table that maps command names to handlers.
- `src/datastore.cpp` – in-memory storage for keys and values.
- `src/resp.cpp` – encode/decode logic for the RESP protocol.
- `include/tinyredis/*.hpp` – headers shared across components.

TODO markers throughout the code highlight the pieces you are expected to implement.

## Building

```bash
cmake -S . -B build
cmake --build build
```

To enable AddressSanitizer and UndefinedBehaviorSanitizer during development:

```bash
cmake -S . -B build-sanitize -DTINYREDIS_ENABLE_SANITIZERS=ON
cmake --build build-sanitize
```

Once you begin filling in the TODOs, add tests or integration scripts as needed (e.g. using the real `redis-cli` against your server).
