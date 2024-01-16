set(
    RENDERER_COMMON_SRC 
    "common/renderer.cpp"
    "common/window_base.cpp"
)

set(
    RENDERER_OPENGL_SRC 
    "opengl/module.cpp"
    "opengl/window.cpp"
)

add_library("renderer-common" STATIC ${RENDERER_COMMON_SRC})
add_library("renderer-opengl" SHARED ${RENDERER_OPENGL_SRC})

find_package(GLEW REQUIRED)

target_link_libraries("renderer-opengl" PRIVATE "GLEW")