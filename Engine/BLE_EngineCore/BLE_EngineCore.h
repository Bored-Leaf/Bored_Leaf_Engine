#pragma once
#include <memory>

class EngineCore {
public:
    EngineCore();
    ~EngineCore();
    void initialise();
    void shutdown();

    // TODO: Register functions only when using dlopen/dlsym
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
