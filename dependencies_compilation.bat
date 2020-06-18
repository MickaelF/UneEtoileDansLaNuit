@echo off
setlocal EnableDelayedExpansion
set Compiler="Visual Studio 16 2019"
set GLFWDir=%~dp0\dependencies\glfw-3.3.2
set GLMDir=%~dp0\dependencies\glm-0.9.9.8
set GLADDir=%~dp0\dependencies\glad-0.1.33
set BuildDirSuffix=build
set InstallDir=%~dp0\thirdParty
mkdir %InstallDir%

echo Building GLFW
xcopy /S %GLFWDir%\CMake %InstallDir%\glfw3\CMake\
xcopy /S %GLFWDir%\deps %InstallDir%\glfw3\deps\
xcopy /S %GLFWDir%\include %InstallDir%\glfw3\include\
xcopy /S %GLFWDir%\src %InstallDir%\glfw3\src\
xcopy %GLFWDir%\CMakeLists.txt %InstallDir%\glfw3\
xcopy %GLFWDir%\cmake_uninstall.cmake.in %InstallDir%\glfw3\

echo Building GLAD
set BuildDir=%GLADDir%\%BuildDirSuffix%
mkdir !BuildDir!
cmake -S %GLADDir% -B "!BuildDir!" -G %Compiler% -DBUILD_SHARED_LIBS=TRUE -DGLAD_API="gl=3.3" -DGLAD_PROFILE=core
cmake --build !BuildDir! 
xcopy /S %BuildDir%\include %InstallDir%\glad\
xcopy /S %BuildDir%\src\glad.c %InstallDir%\glad\

echo Building GLM
xcopy /S %GLMDir%\glm %InstallDir%\glm\

pause