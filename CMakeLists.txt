cmake_minimum_required(VERSION 3.17)
include(generate_input_class.cmake)
message(NOTICE "This project requires Python 3 to work")
set (PROJECT_NAME "AStarInTheNight")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(BUILD_STATIC_LIBS TRUE)

set(InputClassDir ${CMAKE_CURRENT_BINARY_DIR}/inputFiles/)
generate_input_class(InputClassFiles ${InputClassDir})

# ********* SDL2 *********
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/thirdParty/SDL/cmake)
if (WIN32)
    set(SDL2_BASE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/SDL/)
    set(SDL2_INCLUDE_DIRS "${SDL2_BASE_DIR}/include")

    # Support both 32 and 64 bit builds
    if (${CMAKE_BUILD_TYPE} MATCHES Debug)
        set(SDL2_LIBRARIES "${SDL2_BASE_DIR}/lib/SDL2d.lib;${SDL2_BASE_DIR}/lib/SDL2maind.lib")
    else ()
        set(SDL2_LIBRARIES "${SDL2_BASE_DIR}/lib/SDL2.lib;${SDL2_BASE_DIR}/lib/SDL2main.lib")
    endif ()
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif()

# ********* GLAD *********
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/thirdParty/glad/src/glad.c)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glad/include)

add_library(GLAD ${GLAD_SRC})
target_include_directories(GLAD PUBLIC ${GLAD_INCLUDE_DIR})

# ********* GLM *********
set(glm_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glm/lib/cmake/glm)

# ********* stb *********
set(stb_DIR ${CMAKE_SOURCE_DIR}/thirdParty/stb)
set(stb_SRC ${stb_DIR}/stb_image.h)

# ********* ImGUI *********
set(ImGUI_DIR ${CMAKE_SOURCE_DIR}/thirdParty/imgui)
set(ImGUI_HDR src/imgui)
set(ImGUI_SRC
	${ImGUI_DIR}/imgui.cpp
	${ImGUI_DIR}/imgui_draw.cpp
	${ImGUI_DIR}/imgui_widgets.cpp
	${ImGUI_DIR}/imgui_tables.cpp
	${ImGUI_DIR}/backends/imgui_impl_opengl3.cpp
	${ImGUI_DIR}/backends/imgui_impl_sdl.cpp

	src/imgui/iimguiuserinterface.cpp
	src/imgui/imguihandler.cpp)

# ******** PTTK *********
set(PTTK_DIR ${CMAKE_SOURCE_DIR}/thirdParty/pttk/lib/cmake/)
set(PTTK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/pttk/include)

# ******** Assimp *********
set(Assimp_DIR ${CMAKE_SOURCE_DIR}/thirdParty/Assimp/lib/cmake/assimp-5.0/)
set(Assimp_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/Assimp/include)

# ******** FreeType *********
set(Freetype_ROOT ${CMAKE_SOURCE_DIR}/thirdParty/freetype/)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Assimp REQUIRED)
find_package(PTTK REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)


# ********* Application *********
set(SRCS src/main.cpp
	src/mainwindow.cpp
	src/windowinifile.cpp
	src/gameobject.cpp
	src/transform.cpp
	src/mesh.cpp
	src/mesh.h
	src/renderers/texturefactory.cpp
	src/renderers/texture.cpp
	src/model.cpp
	src/basicshader.cpp
	src/shaderutil.cpp
	src/input/action.cpp
	src/input/binding.cpp
	src/input/iactionlistener.h
	src/input/inputhandler.cpp
	src/input/abstractactionmap.cpp
	src/input/abstractcontrolscheme.cpp
	src/iscene.cpp
	src/input/inputrecorder.cpp
	src/appinfo.cpp
	src/renderers/irenderidcard.cpp
	src/renderers/abstractrenderer.cpp
	src/renderers/opengl/openglrenderer.cpp
	src/renderers/opengl/openglidcard.cpp
	src/imgui/appinfowidget.cpp
	src/renderers/opengl/opengltexture.cpp
	src/imgui/textureexplorerwidget.cpp
	)

set(SHADERS
	shaders/glsl/simplevertexshader.vert
	shaders/glsl/simplefragmentshader.frag
	)

add_executable(${PROJECT_NAME} ${SRCS} ${ImGUI_SRC} ${stb_SRC} ${InputClassFiles})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} opengl32 glm::glm ${ASSIMP_LIBRARIES} GLAD PTTK)
target_include_directories(${PROJECT_NAME} PUBLIC src ${ImGUI_HDR} ${InputClassDir} ${ImGUI_DIR} ${Assimp_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${GLM_DIR} ${ImGUI_DIR} ${stb_DIR} ${PTTK_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
