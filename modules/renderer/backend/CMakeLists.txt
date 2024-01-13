set(
    RENDERER_COMMON_SRC 
    "common/renderer.cpp"
    "common/window.cpp"
)

set(
    RENDERER_OPENGL_SRC 
    "opengl/context.cpp"
    "opengl/module_core.cpp"
)

add_library("renderer-common" STATIC ${RENDERER_COMMON_SRC})
add_library("renderer-opengl" SHARED ${RENDERER_OPENGL_SRC})