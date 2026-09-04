#include "ble_engine_core.hpp"
#include "ble_logger.hpp"

#include "job_scheduler.hpp"

namespace ble::engine_core {
    struct EngineCore::Impl {
        
    };

    EngineCore::EngineCore() : impl(std::make_unique<Impl>()) { }
    EngineCore::~EngineCore() = default;

    // Initialises all systems for use
    void EngineCore::initialise() {
        ble::logger::init();
        ble::logger::log(ble::logger::Level::Status, "EngineCore Initialised");
    }

    // Shutsdown all systems
    void EngineCore::shutdown() {
        ble::logger::shutdown();
        ble::logger::log(ble::logger::Level::Status, "EngineCore Shutdown");
    }
}