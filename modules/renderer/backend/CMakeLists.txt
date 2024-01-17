set(
    RENDERER_FRAMEWORK_SRC 
    "framework/module.cpp"
    "framework/renderer.cpp"
    "framework/window_base.cpp"
)

set(
    RENDERER_OPENGL_SRC 
    "opengl/window.cpp"
)

add_library("renderer-framework" SHARED ${RENDERER_FRAMEWORK_SRC})
add_library("renderer-opengl" STATIC ${RENDERER_OPENGL_SRC})

find_package(GLEW REQUIRED)

target_link_libraries("renderer-opengl" PRIVATE "GLEW")