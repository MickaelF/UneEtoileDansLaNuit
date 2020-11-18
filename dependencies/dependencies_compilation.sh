#!/bin/bash
cmakeExe=$1
Compiler="Visual Studio 16 2019"
installDir=$PWD/../thirdParty
QtDir=C:/Qt/5.15.1/msvc2019_64/lib/cmake


GenerateProject()
{
    $cmakeExe -DCMAKE_INSTALL_PREFIX="$installDir/$1" -G "$Compiler" -S "." -B "$PWD/build" -DCMAKE_PREFIX_PATH=$QtDir -DCMAKE_CXX_STANDARD=20 -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DGLAD_API="gl=3.3" -DGLAD_PROFILE=core $2
    if [ ! $? -eq 0 ]; then
        echo "Issue while generating project $1"
    fi

    $cmakeExe --build "$PWD/build" -j 8 --config Release
    if [ ! $? -eq 0 ]; then
        echo "Issue while compiling project $1 in Release"
    fi
    $cmakeExe --install "$PWD/build" --config Release -v

    $cmakeExe --build "$PWD/build" -j 8 --config Debug
    if [ ! $? -eq 0 ]; then
        echo "Issue while compiling project $1 in Debug"
    fi
    $cmakeExe --install "$PWD/build" --config Debug
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

GitUpdate()
{
    folder=$PWD/$1
    echo $folder
    if [ ! -d $PWD/$1 ] ; then
        git clone $2
        if [ ! $? -eq 0 ]; then
            return
        fi
    fi
    cd $1
    git fetch --all
    LastTag
    if [ "$3" = true ]; then
        GenerateProject $1 $3
    else
        CopyFile $1
    fi
    cd ..
}

GLADSpecificInstructions()
{
    mkdir $installDir/glad
    cp -R $PWD/glad/build/include $installDir/glad/include
    cp -R $PWD/glad/build/src $installDir/glad/src
}

GitUpdate glfw https://github.com/glfw/glfw.git true
GitUpdate glm https://github.com/g-truc/glm.git false
GitUpdate glad https://github.com/Dav1dde/glad.git true
GLADSpecificInstructions
GitUpdate imgui https://github.com/ocornut/imgui.git false
GitUpdate PTTK git@github.com:MickaelF/PTTK.git true
GitUpdate stb https://github.com/nothings/stb.git false
GitUpdate Assimp https://github.com/assimp/assimp.git true -DCMAKE_CXX_FLAGS="/Wv:18 /EHsc"