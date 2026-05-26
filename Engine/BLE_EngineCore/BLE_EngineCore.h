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

class EngineCore {
public:
    BLE_API EngineCore();
    BLE_API ~EngineCore();
    BLE_API void initialise();
    BLE_API void shutdown();

    // TODO: Register functions only when using dlopen/dlsym
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
