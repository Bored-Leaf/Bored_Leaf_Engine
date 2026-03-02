#include <print>

#include "BLE_Logger.h"

void print_message(const std::string &message) {
    // TODO:: Wrap escape sequencies to make more readable
    std::print("\033[31m[ERROR]\033[0m {}\n", message);
}