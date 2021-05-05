#!/bin/bash
cmakeExe=$1
prevDir=$PWD
currentDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd $currentDir

Compiler="Visual Studio 16 2019"
installDir=$PWD/../thirdParty
includeDir=$PWD/../include
srcDir=$PWD/../src
QtDir=C:/Qt/5.15.1/msvc2019_64/lib/cmake

BuildProject()
{
    $cmakeExe --build "$1" -j 8 --config $2
    if [ ! $? -eq 0 ]; then
        echo "Issue while compiling project $1 in $2"
    fi
    $cmakeExe --install "$1" --config $2
}

GenerateProject()
{
    if [ "$1" == "Assimp" ]; then
        $cmakeExe -DCMAKE_INSTALL_PREFIX="$installDir/$1" -G "$Compiler" -S "." -B "$PWD/build" -DCMAKE_PREFIX_PATH=$QtDir -DCMAKE_CXX_STANDARD=20 -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF  -DCMAKE_CXX_FLAGS="/Wv:18 /EHsc"
    else
        $cmakeExe -DCMAKE_INSTALL_PREFIX="$installDir/$1" -G "$Compiler" -S "." -B "$PWD/build" -DCMAKE_PREFIX_PATH=$QtDir -DCMAKE_CXX_STANDARD=20
    fi
    if [ ! $? -eq 0 ]; then
        exit
        echo "Issue while generating project $1"
    fi
    BuildProject "$PWD/build" Release
    BuildProject "$PWD/build" Debug
}

LastTag()
{
    latesttag=$(git describe --tags)
    git checkout $latesttag
}

CopyFile()
{
    cp -R . $installDir/$1
}

CopyImgui()
{
    imguiIncludeDir=$includeDir/imgui
    imguiSrcDir=$srcDir/imgui/base
    mkdir -p $imguiIncludeDir
    mkdir -p $imguiSrcDir

    cp ./imconfig.h $imguiIncludeDir
    cp ./imstb*.h $imguiIncludeDir
    cp ./imstb*.cpp $imguiSrcDir
    cp ./imgui*.h $imguiIncludeDir
    cp ./imgui*.cpp $imguiSrcDir
    cp ./backends/imgui_impl_opengl3.h $imguiIncludeDir
    cp ./backends/imgui_impl_sdl.h $imguiIncludeDir
    cp ./backends/imgui_impl_opengl3.cpp $imguiSrcDir
    cp ./backends/imgui_impl_sdl.cpp $imguiSrcDir
    sed -i 's+<SDL+<SDL2/SDL+g' $imguiSrcDir/imgui_impl_sdl.cpp
}

GitUpdate()
{
    folder=$PWD/$1
    echo $folder
    if [ ! -d $folder ] ; then
        git clone $2
        if [ ! $? -eq 0 ]; then
            return
        fi
    fi
    cd $folder
    git fetch --all
    LastTag
    if [ "$3" = true ]; then
        GenerateProject $1
    elif [ "$1" != "imgui" ]; then
        CopyFile $1
    else
        CopyImgui
    fi
    cd ..
}

GenerateGLADFiles()
{
    $cmakeExe  -G "$Compiler" -S "." -B "$PWD/build-$1" -DCMAKE_CXX_STANDARD=20 -DGLAD_API="$2" -DGLAD_PROFILE=core
    BuildProject "$PWD/build-$1" Debug
    BuildProject "$PWD/build-$1" Release

    cp $PWD/build-$1/include/glad/glad.h $includeDir/glad/glad.h
    cp $PWD/build-$1/include/KHR/khrplatform.h $includeDir/KHR/khrplatform.h
    cp $PWD/build-$1/src/glad.c $srcDir/glad/glad.c
    # cp $PWD/build-$1/include/glad/glad.h $includeDir/glad/glad-$1.h
    # cp $PWD/build-$1/include/KHR/khrplatform.h $includeDir/glad/khrplatform-$1.h
    # cp $PWD/build-$1/src/glad.c $srcDir/glad/glad-$1.c
    # sed -i "s+<KHR/khrplatform.h>+<glad/khrplatform-$1.h>+g" $includeDir/glad/glad-$1.h
    # sed -i "s+<glad/glad.h>+<glad/glad-$1.h>+g" $srcDir/glad/glad-$1.c
}

GLADSpecificInstructions()
{
    folder=$PWD/glad
    if [ -d $folder ] ; then
        return
    else
        git clone https://github.com/Dav1dde/glad.git
        if [ ! $? -eq 0 ]; then
            return
        fi
    fi
    cd $folder
    git fetch --all
    LastTag

    mkdir $includeDir/glad
    mkdir $includeDir/KHR
    mkdir $srcDir/glad

    GenerateGLADFiles gl45 gl=4.5
    #GenerateGLADFiles gles31 gles2=3.1
    cd ..
}

CopyStbFiles()
{
    if [ -d $includeDir/stb ] ; then
        return
    fi
    mkdir $includeDir/stb
    cp $installDir/stb/stb_image.h $includeDir/stb/
}

GitUpdate SDL https://github.com/libsdl-org/SDL.git true
GitUpdate glm https://github.com/g-truc/glm.git true
GLADSpecificInstructions
GitUpdate imgui https://github.com/ocornut/imgui.git false
GitUpdate PTTK https://github.com/MickaelF/PTTK.git true
GitUpdate stb https://github.com/nothings/stb.git false
CopyStbFiles
GitUpdate Assimp https://github.com/assimp/assimp.git true
GitUpdate freetype https://github.com/freetype/freetype.git true
cd $prevDir