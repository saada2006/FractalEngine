set(
    FTUL_SRC 
    "src/fractal_common.cpp"
    "src/dynamic_linking.cpp"
)

add_library(ftul STATIC ${FTUL_SRC})

target_include_directories(ftul PUBLIC "include")