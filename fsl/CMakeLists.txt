set(
    FSL_SRC 
    "src/dynamic_linking.cpp"
    "src/engine_core.cpp"
    "src/event_system.cpp"
    "src/fractal.cpp"
    "src/logging.cpp"
    "src/module.cpp"
)

add_library(fsl STATIC ${FSL_SRC})

target_include_directories(fsl PUBLIC "include")
target_compile_definitions(fsl PRIVATE FRACTAL_LOGGING_LOCATION="FTUL Internal")
target_precompile_headers(fsl PUBLIC "include/fsl/std.h" PUBLIC "include/fsl/common.h")