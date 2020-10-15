@echo off
setlocal EnableDelayedExpansion

set Compiler="Visual Studio 16 2019"
set GLFWDir=%~dp0\glfw
set GLMDir=%~dp0\glm
set GLADDir=%~dp0\glad
set ImGUI=%~dp0\imgui
set PTTK=%~dp0\PTTK
set stb=%~dp0\stb
set Assimp=%~dp0\assimp
set BuildDirSuffix=build
set InstallDir=%~dp0\..\thirdParty
mkdir %InstallDir%

rem xcopy : /s = copy recursively; /y = remove command prompt to confirm the copy

echo Handling GLFW 
if not exist %GLFWDir% (
    call git clone https://github.com/glfw/glfw.git
	cd %GLFWDir%	
	call :LastTag
	cd ..
) else (
	cd %GLFWDir%
	call :LastTag
	cd ..
)
xcopy /S /Y %GLFWDir%\CMake %InstallDir%\glfw3\CMake\
xcopy /S /Y %GLFWDir%\deps %InstallDir%\glfw3\deps\
xcopy /S /Y %GLFWDir%\include %InstallDir%\glfw3\include\
xcopy /S /Y %GLFWDir%\src %InstallDir%\glfw3\src\
xcopy /Y %GLFWDir%\CMakeLists.txt %InstallDir%\glfw3\
xcopy /Y %GLFWDir%\cmake_uninstall.cmake.in %InstallDir%\glfw3\

echo Building GLAD 
if not exist %GLADDir% (
    call git clone https://github.com/Dav1dde/glad.git
	cd %GLADDir%	
	call :LastTag
	cd ..
) else (
	cd %GLADDir%
	call :LastTag
	cd ..
)
pause
set BuildDir=%GLADDir%\%BuildDirSuffix%
mkdir !BuildDir!
pause
call cmake -S %GLADDir% -B "!BuildDir!" -G %Compiler% -DBUILD_SHARED_LIBS=TRUE -DGLAD_API="gl=3.3" -DGLAD_PROFILE=core
pause
call cmake --build !BuildDir!
pause
xcopy /S /Y %BuildDir%\include %InstallDir%\glad\
xcopy /Y %BuildDir%\src\glad.c %InstallDir%\glad\

echo Handling GLM
if not exist %GLMDir% (
    call git clone https://github.com/g-truc/glm.git
	cd %GLMDir%	
	call :LastTag
	cd ..
) else (
	cd %GLMDir%
	call :LastTag
	cd ..
)
xcopy /S /Y %GLMDir%\glm %InstallDir%\glm\

echo Handling ImGUI
if not exist %ImGUI% (
    call git clone git@github.com:ocornut/imgui.git
	cd %ImGUI%	
	call :LastTag
	cd ..
) else (
	cd %ImGUI%
	call :LastTag
	cd ..
)
xcopy /Y %ImGUI%\*.h %InstallDir%\imgui\
xcopy /Y %ImGUI%\*.cpp %InstallDir%\imgui\
xcopy /S /Y %ImGUI%\misc %InstallDir%\imgui\

echo Handling PTTK
if not exist %PTTK% (
    call git clone git@github.com:MickaelF/PTTK.git
) else (
	cd %PTTK% 
    call git pull origin default
	cd ..
)
xcopy /S /Y %PTTK%\src %InstallDir%\pttk\src\
xcopy /S /Y %PTTK%\include %InstallDir%\pttk\include\
xcopy /S /Y %PTTK%\extra %InstallDir%\pttk\extra\
xcopy /Y %PTTK%\CMakeLists.txt %InstallDir%\pttk\

echo Handling stb
if not exist %stb% (
    call git clone git@github.com:nothings/stb.git
) else (
    call git pull origin master
)
xcopy /Y %stb%\stb_image.h %InstallDir%\stb\


echo Handling Assimp
if not exist %Assimp% (
    call git clone git@github.com:assimp/assimp.git
	cd %Assimp%
	call :LastTag
	cd ..
) else (
	cd %Assimp%
	call :LastTag
	cd ..
)
xcopy /S /Y %Assimp%\cmake %InstallDir%\assimp\cmake\
xcopy /S /Y %Assimp%\cmake-modules %InstallDir%\assimp\cmake-modules\
xcopy /S /Y %Assimp%\code %InstallDir%\assimp\code\
xcopy /S /Y %Assimp%\contrib %InstallDir%\assimp\contrib\
xcopy /S /Y %Assimp%\include %InstallDir%\assimp\include\
xcopy /S /Y %Assimp%\scripts %InstallDir%\assimp\scripts\
xcopy /S /Y %Assimp%\test %InstallDir%\assimp\test\
xcopy /S /Y %Assimp%\tools %InstallDir%\assimp\tools\
xcopy /Y %Assimp%\CMakeLists.txt %InstallDir%\assimp\
xcopy /Y %Assimp%\*.in %InstallDir%\assimp\

:LastTag
call git describe --abbrev=0 --tags > last.txt	
set /p DATA=<last.txt
call git checkout %DATA%
EXIT /B 0
pause