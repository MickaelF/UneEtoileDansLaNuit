@echo off
setlocal EnableDelayedExpansion
set cmake=C:\Users\Mickael\Documents\Perso\cmake\bin\cmake.exe

set Compiler="Visual Studio 16 2019"
set GLFWDir=%~dp0\glfw-3.3.2
set GLMDir=%~dp0\glm-0.9.9.8
set GLADDir=%~dp0\glad-0.1.33
set ImGUI=%~dp0\imgui-1.76
set PTTK=%~dp0\PTTK
set BuildDirSuffix=build
set InstallDir=%~dp0\..\thirdParty
mkdir %InstallDir%

echo Handling GLFW
xcopy /S /Y %GLFWDir%\CMake %InstallDir%\glfw3\CMake\
xcopy /S /Y %GLFWDir%\deps %InstallDir%\glfw3\deps\
xcopy /S /Y %GLFWDir%\include %InstallDir%\glfw3\include\
xcopy /S /Y %GLFWDir%\src %InstallDir%\glfw3\src\
xcopy /Y %GLFWDir%\CMakeLists.txt %InstallDir%\glfw3\
xcopy /Y %GLFWDir%\cmake_uninstall.cmake.in %InstallDir%\glfw3\

echo Building GLAD
set BuildDir=%GLADDir%\%BuildDirSuffix%
mkdir !BuildDir!
call %cmake% -S %GLADDir% -B "!BuildDir!" -G %Compiler% -DBUILD_SHARED_LIBS=TRUE -DGLAD_API="gl=3.3" -DGLAD_PROFILE=core
call %cmake% --build !BuildDir! 
xcopy /S /Y %BuildDir%\include %InstallDir%\glad\
xcopy /Y %BuildDir%\src\glad.c %InstallDir%\glad\

echo Handling GLM
xcopy /S /Y %GLMDir%\glm %InstallDir%\glm\

echo Handling ImGUI
xcopy /Y %ImGUI%\*.h %InstallDir%\imgui\
xcopy /Y %ImGUI%\*.cpp %InstallDir%\imgui\
xcopy /S /Y %ImGUI%\misc %InstallDir%\imgui\

echo Handling PTTK
if not exist %PTTK% (
    call git clone git@github.com:MickaelF/PTTK.git
) else (
    call git pull origin default
)
xcopy /S /Y %PTTK%\src %InstallDir%\pttk\src\
xcopy /S /Y %PTTK%\include %InstallDir%\pttk\include\
xcopy /S /Y %PTTK%\extra %InstallDir%\pttk\extra\
xcopy /Y %PTTK%\CMakeLists.txt %InstallDir%\pttk\

pause