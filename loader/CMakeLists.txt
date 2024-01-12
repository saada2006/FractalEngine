set(FRACTAL_LOADER_SRC "main.cpp")

add_executable("fractal-loader" ${FRACTAL_LOADER_SRC})

target_link_libraries("fractal-loader" PRIVATE "ftul")