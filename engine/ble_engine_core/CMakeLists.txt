add_library(bored_leaf_engine_core SHARED src/ble_engine_core.cpp)

target_include_directories(bored_leaf_engine_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bored_leaf_engine_core PRIVATE bored_leaf_logger)
target_link_libraries(bored_leaf_engine_core PRIVATE job_scheduler)

target_compile_definitions(bored_leaf_engine_core PRIVATE BLE_BUILD_DLL)
target_compile_options(bored_leaf_engine_core PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:-fvisibility=hidden>
)