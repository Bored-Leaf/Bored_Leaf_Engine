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
     */
    BLE_API void initialise();

    /**
     * @brief Gracefully shutsdown all systems and their resources
     */
    BLE_API void shutdown();

    // TODO: Register functions only when using dlopen/dlsym
private:
        /**
        * @internal
        * @brief Forward-declared implemenation details (PIMPL idiom).
        */
    struct Impl;

        /**
        * @internal
        * @brief Owning pointer to this instance's private implementation.
        */
    std::unique_ptr<Impl> impl;
};
