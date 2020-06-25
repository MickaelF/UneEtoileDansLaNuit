cmake_minimum_required(VERSION 3.14)
message(NOTICE "This project requires Python 3 to work. Don't forget to run the batch script 'dependencies_compilation.bat' at each dependencies change!")

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

# ********* Application *********
set(SRCS src/main.cpp "src/tools/log.h" "src/tools/log.cpp" "src/tools/logger.h" "src/tools/executiontimer.h" "src/tools/logger.cpp" "src/tools/debug.h" "src/file/abstractreader.h" "src/file/abstractreader.cpp" "src/mainwindow.h" "src/mainwindow.cpp")
add_executable(${PROJECT_NAME} ${SRCS} ${ImGUI_SRC})

target_link_libraries(${PROJECT_NAME} glfw opengl32 glm GLAD)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_INCLUDE_DIR} ${GLFW3_INCLUDE_DIRS} ${GLM_DIR} ${ImGUI_SRC})
