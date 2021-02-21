cmake_minimum_required(VERSION 3.17)
project(OGL)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

add_definitions(-DGLEW_STATIC)
# Also possible
# add_compile_definitions(GLEW_STATIC)

message("Including GLEW")
include_directories(libs/glew-2.1.0/include)

set(STB_INCLUDE_PATH PATH src/vendor/stb)

set(LIBS_INCLUDE_PATH
        ${STB_INCLUDE_PATH}
        )
set(VENDOR_INCLUDE_PATH
        src/vendor/stb
        src/vendor/imgui
        )

set(VENDOR_SOURCE_FILES
        src/vendor/stb/stb_image.cpp
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui.h
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_glfw.h
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3.h
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h
        )

set(PROJECT_HEADER_FILES
        src/core/entity/Vertex.h
        src/core/camera/Camera.h
        src/core/shader/Shader.h
        src/core/texture/Texture.h
        src/core/renderer/Renderer.h
        src/core/buffer/index/IndexBuffer.h
        src/core/buffer/vertex/VertexArray.h
        src/core/buffer/vertex/VertexBuffer.h
        src/core/buffer/vertex/VertexBufferLayout.h
        )

set(PROJECT_SOURCE_FILES
        src/core/camera/Camera.cpp
        src/core/shader/Shader.cpp
        src/core/texture/Texture.cpp
        src/core/renderer/Renderer.cpp
        src/core/application/Application.cpp
        src/core/buffer/index/IndexBuffer.cpp
        src/core/buffer/vertex/VertexArray.cpp
        src/core/buffer/vertex/VertexBuffer.cpp
        )

include_directories(OGL
        ${LIBS_INCLUDE_PATH}
        ${VENDOR_INCLUDE_PATH}
        )

add_executable(OGL
        ${PROJECT_SOURCE_FILES}
        ${PROJECT_HEADER_FILES}
        ${VENDOR_SOURCE_FILES}
        )


add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
add_subdirectory(libs/glm)

target_link_libraries(OGL glfw libglew_static glm opengl32)