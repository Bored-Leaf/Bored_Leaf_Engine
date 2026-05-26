#include <print>

#include "BLE_Logger.h"

// Temp solution to quick acess functions for logging.
// TODO: Make a more appropriate design for a logger
namespace BLE::LOGGER {
    void printStatusMessage(const std::string &message) {
        // TODO:: Wrap escape sequencies to make more readable
        std::print("\033[31m[STATUS]\033[0m {}\n", message);
    }
}