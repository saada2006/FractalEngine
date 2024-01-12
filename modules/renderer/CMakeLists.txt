add_subdirectory("backend")

set(ALL_RENDERER_BACKENDS "renderer-opengl")

foreach(RENDERER_BACKEND IN LISTS ALL_RENDERER_BACKENDS)
    target_include_directories(${RENDERER_BACKEND} PRIVATE "include")
    target_link_libraries(${RENDERER_BACKEND} PRIVATE "ftul")
endforeach()