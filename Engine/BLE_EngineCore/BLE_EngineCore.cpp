#include <print>

#include "BLE_EngineCore.h"
#include "BLE_Logger.h"

struct EngineCore::Impl {
    std::unique_ptr<BLE_Logger> logger;
};

EngineCore::EngineCore() : impl(std::make_unique<Impl>()) { }
EngineCore::~EngineCore() = default;

void EngineCore::initialise() {
    impl->logger->print_message("EngineCore Initialised");
}

void EngineCore::shutdown() {
    impl->logger->print_message("EngineCore Shutdown");
}
