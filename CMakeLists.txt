cmake_minimum_required(VERSION 3.3)
set (PROJECT_NAME "AStarInTheNight")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)

set(GLFW3_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glfw3)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW3_DIR})


set(GLAD_SRC ${CMAKE_SOURCE_DIR}/thirdParty/glad/glad.c)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glad/)

add_library(GLAD ${GLAD_SRC})
target_include_directories(GLAD PUBLIC ${GLAD_INCLUDE_DIR})

set(GLM_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glm)
add_subdirectory(${GLM_DIR})

set(SRCS src/main.cpp)
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} glfw opengl32 glm GLAD)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_INCLUDE_DIR} ${GLFW3_INCLUDE_DIRS} ${GLM_DIR})
