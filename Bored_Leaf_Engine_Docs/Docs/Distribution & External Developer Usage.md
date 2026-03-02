Rewrite when the time comes

## Two ways to use the engine

- **Build from source** — clone the repo, build with CMake, run `cmake --install` to produce the distributable folder. For developers who need to modify the engine or build for an unsupported platform.
- **Pre-built release** — download and unzip a pre-built release from GitHub. No build step required. The recommended option for most developers.

## What a release contains

A clean folder structure with:

- `.so`/`.dll` files for each system
- Public headers
- CMake config files

## CMake config files

Included in the release so external developers can use `find_package` regardless of where they extracted the release to. Paths are relative so they work on any machine.

## find_package options

Two levels of granularity:

- `find_package(Bored_Leaf_Engine)` — convenience, finds all systems at once
- `find_package(BLE_Renderer)` etc. — finds a single system, aligns with modularity goal for developers who only need specific systems