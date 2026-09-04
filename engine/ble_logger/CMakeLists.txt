add_library(bored_leaf_logger SHARED src/ble_logger.cpp)

target_include_directories(bored_leaf_logger
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
