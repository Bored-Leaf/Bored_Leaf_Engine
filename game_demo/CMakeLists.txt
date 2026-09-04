add_executable(bored_leaf_engine_demo main.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(bored_leaf_engine_demo PRIVATE -stdlib=libc++)
    target_link_options(bored_leaf_engine_demo PRIVATE -stdlib=libc++ -lc++abi)
endif()

target_link_libraries(bored_leaf_engine_demo PRIVATE bored_leaf_engine_core)