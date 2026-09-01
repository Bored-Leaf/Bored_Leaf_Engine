#pragma once

#if defined(_WIN32)
    #if defined(BLE_BUILD_DLL)
        #define BLE_API __declspec(dllexport)
    #else
        #define BLE_API __declspec(dllimport)
    #endif
#else
    #define BLE_API __attribute__((visibility("default")))
#endif

#include <memory>
namespace ble::engine_core {
    /**
    * @brief Central object of the game engine.
    * @details Basically the starting point of the game engine that has
    * restricted access to every system.
    */
    class EngineCore {
    public:
        BLE_API EngineCore();
        BLE_API ~EngineCore();

        /**
        * @brief Initialises all systems for use
        *
        * @note very simple for now but when dynamic libary loading is implemented will
        * be a little more complex
        */
        BLE_API void initialise();

        /**
        * @brief Gracefully shutsdown all systems and their resources
        */
        BLE_API void shutdown();

        // TODO: Register functions only when using dlopen/dlsym
        // Don't forget have to register functions before initialise.
    private:
        /**
        * @internal
        * @brief Forward-declared implemenation details (PIMPL idiom).
        * @details Contains members of the engines systems
        */
        struct Impl;

        /**
        * @internal
        * @brief Owning pointer to this instance's private implementation.
        */
        std::unique_ptr<Impl> impl;
    };
}