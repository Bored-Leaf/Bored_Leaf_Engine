#include "ble_engine_core.hpp"

int main() {
    ble::engine_core::EngineCore engine{};

    engine.initialise();

    engine.shutdown();

    return 1;
}