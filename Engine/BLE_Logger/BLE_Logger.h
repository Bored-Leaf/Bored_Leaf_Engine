#pragma once

#include <string>

class BLE_Logger {
public:
    BLE_Logger();

    void print_message(const std::string &message);
};