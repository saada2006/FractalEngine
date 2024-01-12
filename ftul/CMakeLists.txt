set(
    FTUL_SRC 
    "src/ftul_init.cpp"
)

add_library(ftul STATIC ${FTUL_SRC})

target_include_directories(ftul PUBLIC "include")