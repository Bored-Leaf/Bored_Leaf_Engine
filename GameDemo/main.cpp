#include <print>

#include "BLE_EngineCore.h"

int main() {
    std::print("Hello, from GameDemo\n");

    EngineCore engine{};

    engine.initialise();
    engine.shutdown();

    return 1;
}