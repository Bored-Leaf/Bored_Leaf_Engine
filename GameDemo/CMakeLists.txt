add_executable(Bored_Leaf_Engine_Demo main.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(Bored_Leaf_Engine_Demo PRIVATE -stdlib=libc++)
    target_link_options(Bored_Leaf_Engine_Demo PRIVATE -stdlib=libc++ -lc++abi)
endif()

target_link_libraries(Bored_Leaf_Engine_Demo PRIVATE Bored_Leaf_EngineCore)