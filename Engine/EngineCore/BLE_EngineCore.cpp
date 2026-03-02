#include <print>

#include "BLE_EngineCore.h"
#include "BLE_Logger.h"

void say_hello() {
    std::print("Hello from Bored Leaf EngineCore\n");
    print_message("Hello has been said");
}