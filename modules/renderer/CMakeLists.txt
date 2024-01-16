add_subdirectory("backend")

set(ALL_RENDERER_BACKENDS "renderer-opengl")
set(ALL_RENDERER_TARGETS ${ALL_RENDERER_BACKENDS} "renderer-common")

foreach(RENDERER_TARGET IN LISTS ALL_RENDERER_TARGETS)
    target_include_directories(${RENDERER_TARGET} PRIVATE "include" ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${RENDERER_TARGET} PRIVATE "fsl" ${SDL2_LIBRARIES})
    target_compile_definitions(${RENDERER_TARGET} PRIVATE FRACTAL_LOGGING_LOCATION="Renderer")
endforeach()

foreach(RENDERER_BACKEND IN LISTS ALL_RENDERER_BACKENDS)
    target_link_libraries(${RENDERER_BACKEND} PRIVATE "renderer-common")
endforeach()

