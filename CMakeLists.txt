cmake_minimum_required(VERSION 3.28)

project(lean-engine LANGUAGES CXX)

# source files
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

# use CPM
include(cmake/CPM.cmake)

# GLAD
CPMAddPackage(
  NAME glad
  GITHUB_REPOSITORY Dav1dde/glad
  VERSION 0.1.36
)

# GLM
CPMAddPackage(
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 0.9.9.8
)

# GLFW & IMGUI
CPMAddPackage(
  NAME imgui_cmake_wrapper
  GITHUB_REPOSITORY matekdev/imgui_cmake_wrapper
  GIT_TAG main
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glm imgui_cmake_wrapper)

# Copy shader files
add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shaders
        ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/shaders
        COMMENT "Copying shaders into binary directory")

add_dependencies(${PROJECT_NAME} copy_shaders)