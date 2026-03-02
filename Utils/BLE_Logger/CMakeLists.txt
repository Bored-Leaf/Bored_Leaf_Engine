add_library(BLE_Logger STATIC BLE_LOGGER.cpp)

target_include_directories(BLE_Logger
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)