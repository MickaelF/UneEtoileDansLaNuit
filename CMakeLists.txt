cmake_minimum_required(VERSION 3.14)
message(NOTICE "This project requires Python 3 to work")
set (PROJECT_NAME "AStarInTheNight")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
find_package(OpenGL REQUIRED)

# ********* GLW3 *********
set(GLFW3_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glfw3)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW3_DIR})

# ********* GLAD *********
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/thirdParty/glad/glad.c)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glad/)

add_library(GLAD ${GLAD_SRC})
target_include_directories(GLAD PUBLIC ${GLAD_INCLUDE_DIR})

# ********* GLM *********
set(GLM_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glm)
add_subdirectory(${GLM_DIR})

# ********* ImGUI *********
set(ImGUI_DIR ${CMAKE_SOURCE_DIR}/thirdParty/imgui)
set(ImGUI_SRC 
	${ImGUI_DIR}/imgui.cpp
	${ImGUI_DIR}/imgui_demo.cpp
	${ImGUI_DIR}/imgui_draw.cpp
	${ImGUI_DIR}/imgui_widgets.cpp)

# ******** PTTK *********
set(PTTK_DIR ${CMAKE_SOURCE_DIR}/thirdParty/pttk)
set(PTTK_BUILD_CMD_LOG_PARSER OFF CACHE BOOL "" FORCE)
set(PTTK_BUILD_LOG_GENERATOR ON CACHE BOOL "" FORCE)
set(PTTK_BUILD_QT_WIDGET_LOG_PARSER OFF CACHE BOOL "" FORCE)
add_subdirectory(${PTTK_DIR})

# ********* Application *********
set(SRCS src/main.cpp 
	src/mainwindow.h 
	src/mainwindow.cpp 
	src/windowinifile.h 
	src/windowinifile.cpp)

set(HDRS src/file/
	src/tools/)

add_executable(${PROJECT_NAME} ${SRCS} ${ImGUI_SRC})

target_link_libraries(${PROJECT_NAME} glfw opengl32 glm GLAD PTTK)
target_include_directories(${PROJECT_NAME} PUBLIC ${HDRS} ${GLAD_INCLUDE_DIR} ${GLM_DIR} ${ImGUI_SRC} ${PTTK_INCLUDE_DIR})
