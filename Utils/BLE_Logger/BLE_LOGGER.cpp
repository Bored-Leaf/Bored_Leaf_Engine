#include <print>

#include "BLE_LOGGER.h"

void print_message(const std::string &message) {
    std::print("{}\n", message);
}