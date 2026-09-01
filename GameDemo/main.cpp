#include "BLE_EngineCore.h"

int main() {
    ble::engine_core::EngineCore engine{};

    engine.initialise();

    engine.shutdown();

    return 1;
}