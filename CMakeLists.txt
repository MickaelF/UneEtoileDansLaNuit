cmake_minimum_required(VERSION 3.14)
message(NOTICE "This project requires Python 3 to work")
set (PROJECT_NAME "AStarInTheNight")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(BUILD_STATIC_LIBS TRUE)
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

# ********* stb *********
set(stb_DIR ${CMAKE_SOURCE_DIR}/thirdParty/stb)
set(stb_SRC ${stb_DIR}/stb_image.h)

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
set(PTTK_BUILD_LOG_GENERATOR OFF CACHE BOOL "" FORCE)
set(PTTK_BUILD_QT_WIDGET_LOG_PARSER OFF CACHE BOOL "" FORCE)
add_subdirectory(${PTTK_DIR})

# ******** Assimp *********
set(Assimp_DIR ${CMAKE_SOURCE_DIR}/thirdParty/assimp)
set(Assimp_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/assimp/include)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(${Assimp_DIR})

# ********* Application *********
set(SRCS src/main.cpp 
	src/mainwindow.cpp 
	src/windowinifile.cpp
	src/gameobject.cpp	
	src/transform.cpp
	src/mesh.cpp
	src/mesh.h
	src/texturefactory.cpp
	src/texture.cpp
	src/model.cpp
	src/basicshader.cpp
	src/shaderutil.cpp
	)

set(SHADERS
	shaders/glsl/simplevertexshader.vert
	shaders/glsl/simplefragmentshader.frag
	)

add_executable(${PROJECT_NAME} ${SRCS} ${ImGUI_SRC} ${stb_SRC})

target_link_libraries(${PROJECT_NAME} glfw opengl32 glm_static assimp GLAD PTTK)
target_include_directories(${PROJECT_NAME} PUBLIC ${Assimp_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${GLM_DIR} ${ImGUI_SRC} ${stb_DIR} ${PTTK_INCLUDE_DIR})
