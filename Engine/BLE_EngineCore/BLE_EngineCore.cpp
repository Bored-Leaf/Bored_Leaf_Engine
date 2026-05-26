#include "BLE_EngineCore.h"
#include "BLE_Logger.h"

struct EngineCore::Impl {
    
};

EngineCore::EngineCore() : impl(std::make_unique<Impl>()) { }
EngineCore::~EngineCore() = default;

// Initialises all systems for use
void EngineCore::initialise() {
    // TODO: Make Logger a static/global thing so everything has fast access to. log member functions writes to console and log file same time for now, just make simple.
    BLE::LOGGER::printStatusMessage("EngineCore Initialised");
}

// Shutsdown all systems
void EngineCore::shutdown() {
    BLE::LOGGER::printStatusMessage("EngineCore Shutdown");
}
