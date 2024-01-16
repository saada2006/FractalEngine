set(
    FTUL_SRC 
    "src/dynamic_linking.cpp"
    "src/engine_core.cpp"
    "src/event_system.cpp"
    "src/fractal_common.cpp"
    "src/logging.cpp"
)

add_library(ftul STATIC ${FTUL_SRC})

target_include_directories(ftul PUBLIC "include")
target_compile_definitions(ftul PRIVATE FRACTAL_LOGGING_LOCATION="FTUL Internal")