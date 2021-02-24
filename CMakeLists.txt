cmake_minimum_required(VERSION 3.17)
project(OGL)

set(CMAKE_CXX_STANDARD 20)

include(src/vendor/CMakeLists.txt)

set(PROJECT_HEADER_FILES
        src/pch.h
        src/core/input/Input.h
        src/core/entity/Vertex.h
        src/core/shader/Shader.h
        src/core/texture/Texture.h
        src/platform/WindowsWindow.h
        src/core/application/Window.h
        src/core/application/Application.h
        src/core/buffer/index/IndexBuffer.h
        src/core/camera/OrthographicCamera.h
        src/core/buffer/vertex/VertexArray.h
        src/core/buffer/vertex/VertexBuffer.h
        src/core/buffer/vertex/VertexBufferLayout.h
        )

set(PROJECT_SOURCE_FILES
        src/pch.cpp
        src/sandbox/Sandbox.cpp
        src/core/shader/Shader.cpp
        src/core/texture/Texture.cpp
        src/platform/WindowsInput.cpp
        src/platform/WindowsWindow.cpp
        src/core/application/Window.cpp
        src/core/application/Application.cpp
        src/core/buffer/index/IndexBuffer.cpp
        src/core/camera/OrthographicCamera.cpp
        src/core/buffer/vertex/VertexArray.cpp
        src/core/buffer/vertex/VertexBuffer.cpp
        )

include_directories(OGL ${VENDOR_INCLUDE_PATH})

add_executable(OGL
        ${PROJECT_SOURCE_FILES}
        ${PROJECT_HEADER_FILES}
        ${VENDOR_SOURCE_FILES})

message("Linking GLFW")
add_subdirectory(libs/glfw)
target_link_libraries(OGL glfw)

message("Linking GLEW")
add_definitions(-DGLEW_STATIC)
add_subdirectory(libs/glew)
target_link_libraries(OGL libglew_static)

message("Linking GLM")
add_subdirectory(libs/glm)
target_link_libraries(OGL glm)