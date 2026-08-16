#include "BLE_EngineCore.h"
#include "BLE_Logger.h"

struct EngineCore::Impl {
    
};

EngineCore::EngineCore() : impl(std::make_unique<Impl>()) { }
EngineCore::~EngineCore() = default;

// Initialises all systems for use
void EngineCore::initialise() {
    // TODO: Make Logger a static/global thing so everything has fast access to. log member functions writes to console and log file same time for now, just make simple.
    ble::logger::init();
    ble::logger::log(ble::logger::Level::Status, "EngineCore Initialised");
}

// Shutsdown all systems
void EngineCore::shutdown() {
    ble::logger::shutdown();
    ble::logger::log(ble::logger::Level::Status, "EngineCore Shutdown");
}
