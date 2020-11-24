cmake_minimum_required(VERSION 3.17)
message(NOTICE "This project requires Python 3 to work")
set (PROJECT_NAME "AStarInTheNight")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(BUILD_STATIC_LIBS TRUE)

# ********* GLW3 *********
set(glfw3_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glfw/lib/cmake/glfw3)

# ********* GLAD *********
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/thirdParty/glad/src/glad.c)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glad/include)

add_library(GLAD ${GLAD_SRC})
target_include_directories(GLAD PUBLIC ${GLAD_INCLUDE_DIR})

# ********* GLM *********
set(glm_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glm/cmake/glm)

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
set(PTTK_DIR ${CMAKE_SOURCE_DIR}/thirdParty/pttk/lib/cmake/)
set(PTTK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/pttk/include)

# ******** Assimp *********
set(Assimp_DIR ${CMAKE_SOURCE_DIR}/thirdParty/Assimp/lib/cmake/assimp-5.0/)
set(Assimp_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/Assimp/include)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Assimp REQUIRED)
find_package(PTTK REQUIRED)
find_package(glfw3 REQUIRED)


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
	src/input/action.cpp
	src/input/binding.cpp
	src/input/iactionlistener.h
	src/input/input.h
	src/input/inputhandler.cpp
	)

set(SHADERS
	shaders/glsl/simplevertexshader.vert
	shaders/glsl/simplefragmentshader.frag
	)

add_executable(${PROJECT_NAME} ${SRCS} ${ImGUI_SRC} ${stb_SRC})
target_link_libraries(${PROJECT_NAME} glfw opengl32 glm::glm ${ASSIMP_LIBRARIES} GLAD PTTK)
target_include_directories(${PROJECT_NAME} PUBLIC ${Assimp_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${GLM_DIR} ${ImGUI_SRC} ${stb_DIR} ${PTTK_INCLUDE_DIR})
