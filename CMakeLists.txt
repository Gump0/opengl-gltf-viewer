cmake_minimum_required(VERSION 3.10)
project(gltf-viewer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
)

# imgui stuff
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/include/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

add_executable(gltf-viewer ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(gltf-viewer PRIVATE
    include
    src
)

target_link_libraries(gltf-viewer
    glfw
    OpenGL::GL
)

# always output executable to build/
set_target_properties(gltf-viewer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# copy shaders next to executable after every build
add_custom_command(TARGET gltf-viewer POST_BUILD
    # copy shaders dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
    ${CMAKE_BINARY_DIR}/shaders

    # copy models dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/models
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_BINARY_DIR}/models
)

# run target so you can do: cmake --build build --target run
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/gltf-viewer
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS gltf-viewer
)
