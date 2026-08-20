#pragma once

#include <string>

/*
    Logger with free functions that logs to a terminal
    and file.

    Only logs engine stuff for now, will add user defind 
    logs in a later addition to the logger
*/
// NEXT: Start doxygen
// @internal for not public exposed API
namespace ble::logger {
    void init();    
    void shutdown();

    enum class Level : uint8_t {
        Status,
        Warning,
        Error,
        Fatal,
        Count
    };

    void log(Level level, const std::string &message);
    void print(Level level, const std::string &message);
    void write(Level level, const std::string &message);
}