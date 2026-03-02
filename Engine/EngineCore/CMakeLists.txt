add_library(Bored_Leaf_EngineCore SHARED BLE_EngineCore.cpp)

target_include_directories(Bored_Leaf_EngineCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Bored_Leaf_EngineCore PRIVATE BLE_Logger)