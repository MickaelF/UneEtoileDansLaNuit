cmake_minimum_required(VERSION 3.17)
#message(NOTICE "This project requires Python 3 to work")
set (PROJECT_NAME "UneEtoile")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_STATIC_LIBS TRUE)

option(UneEtoile_BUILD_Model_Viewer "Build the Model Viewer" ON)
set (UneEtoile_BUILD_Model_Viewer ON)


set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# To add a correct version number, one day, see https://www.mattkeeter.com/blog/2018-01-06-versioning/

set(INCLUDED_LIBS "Threads::Threads;${CMAKE_DL_LIBS}")
# ********* GLAD *********
set(GLAD_SRC
	src/glad/glad.c)

# ********* SDL2 *********
set(SDL2_BASE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/SDL/)
set(SDL2_INCLUDE_DIR "${SDL2_BASE_DIR}/include")
if (WIN32)
	set(SDL2_DIR ${CMAKE_SOURCE_DIR}/thirdParty/SDL/cmake)

    # Support both 32 and 64 bit builds
    if (${CMAKE_BUILD_TYPE} MATCHES Debug)
        set(SDL2_LIBRARIES "${SDL2_BASE_DIR}lib/SDL2d.lib;${SDL2_BASE_DIR}lib/SDL2maind.lib")
    else ()
        set(SDL2_LIBRARIES "${SDL2_BASE_DIR}lib/SDL2.lib;${SDL2_BASE_DIR}lib/SDL2main.lib")
    endif ()
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

	set(INCLUDED_LIBS "${INCLUDED_LIBS};${SDL2_LIBRARIES}")
elseif(UNIX)
	set(SDL2_DIR ${CMAKE_SOURCE_DIR}/thirdParty/SDL/lib/cmake/SDL2/)
	set(SDL2_LIBRARIES "${SDL2_BASE_DIR}lib/libSDL2.a;${SDL2_BASE_DIR}lib/libSDL2main.a")
	set(INCLUDED_LIBS "${INCLUDED_LIBS};${SDL2_LIBRARIES}")
endif()

# ********* GLM *********
set(glm_DIR ${CMAKE_SOURCE_DIR}/thirdParty/glm/lib/cmake/glm)
set(INCLUDED_LIBS "${INCLUDED_LIBS};glm::glm")

# ********* stb *********
set(stb_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/stb)

# ********* ImGUI *********
set(ImGui_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/imgui)
set(ImGui_SRC
	src/imgui/base/imgui_draw.cpp
	src/imgui/base/imgui.cpp
	src/imgui/base/imgui_tables.cpp
	src/imgui/base/imgui_widgets.cpp
	src/imgui/base/imgui_impl_opengl3.cpp
	src/imgui/base/imgui_impl_sdl.cpp
	)

# ******** PTTK *********
set(PTTK_DIR ${CMAKE_SOURCE_DIR}/thirdParty/PTTK/lib/cmake/)
set(PTTK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/PTTK/include)
set(INCLUDED_LIBS "${INCLUDED_LIBS};PTTK")

# ******** Assimp *********
set(assimp_DIR ${CMAKE_SOURCE_DIR}/thirdParty/assimp/lib/cmake/assimp-5.0/)
set(assimp_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdParty/assimp/include)
set(INCLUDED_LIBS "${INCLUDED_LIBS};${ASSIMP_LIBRARIES}")

# ******** FreeType *********
set(Freetype_ROOT ${CMAKE_SOURCE_DIR}/thirdParty/freetype/)
set(INCLUDED_LIBS "${INCLUDED_LIBS};${FREETYPE_LIBRARIES}")

find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_package(PTTK REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)
find_package(Threads REQUIRED)
find_library(OpenGLES2_LIBRARY GLESv2)
set(GraphLibFile "#pragma once

")
if (OpenGLES2_LIBRARY)
    set(GraphLibFile "${GraphLibFile}#define OPENGLES2_FOUND 
    ")
	set(INCLUDED_LIBS "${INCLUDED_LIBS};${OpenGLES2_LIBRARY}")
else()
    find_package(OpenGL)
    if (${OpenGL_FOUND})
        set(GraphLibFile "${GraphLibFile}#define OPENGL_FOUND 
        ")
	    set(INCLUDED_LIBS "${INCLUDED_LIBS};opengl32")
	endif()
endif()
find_package(Vulkan)
if (${Vulkan_FOUND})
	set(INCLUDED_LIBS "${INCLUDED_LIBS};Vulkan")
	set(GraphLibFile "${GraphLibFile}#define VULKAN_FOUND
    ")
endif()

file(WRITE include/UneEtoile/render/renderermacros.h "${GraphLibFile}")



# ********* Application *********
set(SRCS
	src/window/mainwindow.cpp
	src/window/windowinifile.cpp
	src/scene/gameobject.cpp
	src/scene/transform.cpp
	src/scene/mesh.cpp
	src/render/texturefactory.cpp
	src/render/texture.cpp
	src/scene/model.cpp
	src/render/opengl/openglshader.cpp
	src/input/action.cpp
	src/input/binding.cpp
	src/input/inputhandler.cpp
	src/input/abstractactionmap.cpp
	src/input/abstractcontrolscheme.cpp
	src/scene/iscene.cpp
	src/input/inputrecorder.cpp
	src/appinfo.cpp
	src/render/irenderidcard.cpp
	src/render/abstractrenderer.cpp
	src/render/opengl/openglrenderer.cpp
	src/render/opengl/openglidcard.cpp
	src/imgui/widget/appinfowidget.cpp
	src/render/opengl/opengltexture.cpp
	src/imgui/widget/textureexplorerwidget.cpp
	src/imgui/iimguiuserinterface.cpp
	src/imgui/imguihandler.cpp
	src/render/abstractshader.cpp
	src/scene/camera.cpp
	src/imgui/widget/camerawidget.cpp
	src/imgui/widget/controlschemewidget.cpp
	src/input/bindingfactory.cpp
	src/input/cameramanipulation.cpp
)

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Create the UneEtoileConfig.cmake and UneEtoileConfig files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(UneEtoileConfig.cmake.in
  "${PROJECT_BINARY_DIR}/UneEtoileConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${PTTK_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(UneEtoileConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/UneEtoileConfig.cmake" @ONLY)
# ... for both
configure_file(UneEtoileConfig.cmake.in
  "${PROJECT_BINARY_DIR}/UneEtoileConfigVersion.cmake" @ONLY)

add_library(${PROJECT_NAME} ${SRCS} ${GLAD_SRC} ${ImGui_SRC} ${InputClassFiles})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INCLUDED_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>
)
target_include_directories(${PROJECT_NAME} PRIVATE ${ImGui_INCLUDE_DIR} ${assimp_INCLUDE_DIR} ${GLM_DIR}  ${stb_INCLUDE_DIR} ${PTTK_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})


install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
	LIBRARY  DESTINATION "lib${LIB_SUFFIX}"
	ARCHIVE DESTINATION "lib${LIB_SUFFIX}"
	RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT ${PROJECT_NAME}Targets
        FILE UneEtoileTargets.cmake
        DESTINATION lib/cmake)
install(FILES
	"${PROJECT_BINARY_DIR}/UneEtoileConfigVersion.cmake"
	"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/UneEtoileConfig.cmake"
	DESTINATION lib/cmake)

if (UneEtoile_BUILD_Model_Viewer)
	add_subdirectory(extra/ModelViewer)
endif()