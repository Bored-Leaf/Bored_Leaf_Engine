add_library(Bored_Leaf_EngineCore SHARED BLE_EngineCore.cpp)

target_include_directories(Bored_Leaf_EngineCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Bored_Leaf_EngineCore PRIVATE Bored_Leaf_Logger)

target_compile_definitions(Bored_Leaf_EngineCore PRIVATE BLE_BUILD_DLL)
target_compile_options(Bored_Leaf_EngineCore PRIVATE
$<$<NOT:$<BOOL:${WIN32}>>:-fvisibility=hidden>
)