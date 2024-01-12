set(RENDERER_COMMON_SRC "common/window.cpp")

set(RENDERER_OPENGL_SRC "opengl/renderer_common.cpp")

add_library("renderer-opengl" SHARED ${RENDERER_OPENGL_SRC} ${RENDERER_COMMON_SRC})