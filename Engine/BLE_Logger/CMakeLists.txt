add_library(Bored_Leaf_Logger SHARED BLE_Logger.cpp)

target_include_directories(Bored_Leaf_Logger
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
