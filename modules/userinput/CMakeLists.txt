
set(
    USER_INPUT_SRC 
    "module.cpp"
)

add_library("user-input" SHARED ${USER_INPUT_SRC})

target_include_directories("user-input" PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries("user-input" PRIVATE "ftul" ${SDL2_LIBRARIES})
target_compile_definitions("user-input" PRIVATE FRACTAL_LOGGING_LOCATION="User Input") 