#include "job_scheduler.hpp"
#include "event_bus.hpp"

#include "ble_engine_core.hpp"
#include "ble_logger.hpp"

// NEXT: Make ECS.
// Wire up job_scheduler/EventBus/ECS don't know 
// how going to wire them up though just yet.
// Need to do these before window and input system

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