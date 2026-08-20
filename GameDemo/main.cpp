#include "BLE_EngineCore.h"

int main() {
    EngineCore engine{};

    engine.initialise();

    engine.shutdown();

    return 1;
}