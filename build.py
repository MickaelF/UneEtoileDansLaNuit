#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, os.path
import json
import argparse
import subprocess
import shutil
import fileinput
import stat

workingdir = os.getcwd()
cmakeDefaultOptions = []
isWindowsOS = (os.name == 'nt')

def set_rw(operation, name, exc):
    if not os.path.exists(name):
        return True
    os.chmod(name, stat.S_IWRITE)
    return True

def openJsonFile(path):
    f = open(path)
    data = json.load(f)
    f.close()
    return data

def needsToBeUpdated(name, data):
    if not os.path.exists("lastUpdate.json"):
        return False
    lastUpdateJson = openJsonFile("lastUpdate.json".format(workingdir, name))
    for key in lastUpdateJson.keys():
        if data[key] != lastUpdateJson[key]:
            return True

    return False

def createJsonFile(path, data):
    f = open(path, "w")
    f.write(json.dumps(data))
    f.close()

def handleSpecialCommands(orig, dest, operations, clean = False):
    def replacePlaceholders(str):
        dict = {
            "${DEP_DIR}": orig,
            "${INSTALL_DIR}": dest,
            "${INCLUDE_DIR}": "{0}/include".format(workingdir),
            "${SRC_DIR}": "{0}/src".format(workingdir)
        }
        for i, j in dict.items():
            str = str.replace(i, j)
        return str

    for operation in operations:
        if operation["operation"] == "copy":
            if "files" in operation:
                for file in operation["files"]:
                    origDir = replacePlaceholders(file["folder"])
                    destDir = replacePlaceholders(file["dest"])
                    if not clean:
                        os.makedirs(destDir, exist_ok=True)
                        for filename in file["files"]:
                            shutil.copyfile("{0}/{1}".format(origDir, filename), "{0}/{1}".format(destDir, filename))
                    else:
                         for filename in file["files"]:
                            os.remove("{0}/{1}".format(destDir, filename))

            if "directories" in operation:
                for directory in operation["directories"]:
                    dest = replacePlaceholders(directory["dest"])
                    if os.path.exists(dest) or clean:
                        shutil.rmtree(dest, onerror=set_rw)
                    if not clean:
                        shutil.copytree(replacePlaceholders(directory["orig"]), dest)
        elif operation["operation"] == "replace":
            for fileJson in operation["files"]:
                with fileinput.FileInput(replacePlaceholders(fileJson["path"]), inplace=True, backup='.bak') as file:
                    for line in file:
                        print(line.replace(fileJson["change"], fileJson["to"]))


def parseDependenciesJson(args):
    data = openJsonFile('{0}/dependencies/dependencies.json'.format(workingdir))
    cmakeOptions = data["cmake"]
    cmakeDefaultOptions.append(args.cmake)
    if not args.generator:
        if isWindowsOS:
            cmakeDefaultOptions.append("-G")
            cmakeDefaultOptions.append(cmakeOptions["windows"]["generator"])
        else:
            cmakeDefaultOptions.append("-G")
            cmakeDefaultOptions.append(cmakeOptions["linux"]["generator"])

    cmakeDefaultOptions.append("-DCMAKE_CXX_STANDARD=20")

    os.chdir("dependencies")
    for dependency in data["dependencies"]:
        print("""
        ************************************************************************
                                     {0}
        ************************************************************************
        """.format(dependency["name"]))
        destPath = "{0}/{1}".format(args.d, dependency["name"])
        if args.action == "clean" and os.path.exists(dependency["name"]):
            shutil.rmtree("{0}/dependencies/{1}".format(workingdir, dependency["name"]), onerror=set_rw)
            shutil.rmtree(destPath, onerror=set_rw)
            if "special" in dependency:
                handleSpecialCommands(os.getcwd(), destPath, dependency["special"], True)

        if args.action == "build":
            if os.path.exists(dependency["name"]):
                os.chdir(dependency["name"])
                if not os.path.exists("lastUpdate.json"):
                    createJsonFile("lastUpdate.json".format(workingdir, dependency["name"]), dependency)
                elif needsToBeUpdated(dependency["name"], dependency):
                    shutil.rmtree("build", onerror=set_rw)
                    os.remove("lastUpdate.json")
                    subprocess.call(["git", "checkout", dependency["branch"]])
                    createJsonFile("lastUpdate.json".format(workingdir, dependency["name"]), dependency)
            else:
                subprocess.call(["git", "clone", dependency["url"], "-b", dependency["branch"]])
                createJsonFile("{0}/dependencies/{1}/lastUpdate.json".format(workingdir, dependency["name"]), dependency)
                os.chdir(dependency["name"])

            if (dependency["build"] == True):
                cmake = cmakeDefaultOptions.copy()
                cmake.append("-DCMAKE_INSTALL_PREFIX={0}".format(destPath))
                cmake.append("-B")
                cmake.append("build")
                if "cmakeBuildOptions" in dependency:
                    cmake.extend(dependency["cmakeBuildOptions"])
                if dependency["name"] == "SDL":
                    cmake.append("-DVIDEO_RPI={0}".format("ON" if args.graphicalAPI == "RaspberryPi" else "OFF"))
                    cmake.append("-DVIDEO_OPENGL={0}".format("ON" if args.graphicalAPI == "OpenGL" else "OFF"))
                    cmake.append("-DVIDEO_VULKAN={0}".format("ON" if args.graphicalAPI == "Vulkan" else "OFF"))
                    cmake.append("-DVIDEO_OPENGLES={0}".format("ON" if args.graphicalAPI == "OpenGLES" else "OFF"))
                    cmake.append("-DDIRECTX={0}".format("ON" if args.graphicalAPI == "DirectX" else "OFF"))
                    print(cmake)
                if dependency["name"] == "glad":
                    if args.graphicalAPI == "OpenGL":
                        cmake.append("-DGLAD_API=\"gl={0}\"".format(dependency["version"]["gl"]))
                    elif args.graphicalAPI == "OpenGLES" or args.graphicalAPI == "RaspberryPi":
                        cmake.append("-DGLAD_API=\"gles2={0}\"".format(dependency["version"]["gles2"]))
                subprocess.call(cmake)
                subprocess.call([args.cmake, "--build", "build", "-j", "8", "--config", args.buildType])
                subprocess.call([args.cmake, "--build", "build", "-j", "8", "--config", args.buildType, "--target", "install"])
            if "special" in dependency:
                handleSpecialCommands(os.getcwd(), destPath, dependency["special"])
            os.chdir("..")


# main
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("action", default="build", choices=["build", "clean"], help="The action that needs to be done when calling this script")
    parser.add_argument("-B", default="{0}/".format(workingdir), help="Where the build folder will be located.")
    parser.add_argument("-d", default="{0}/thirdParty".format(workingdir), help="Where the dependencies will be installed.")
    parser.add_argument("-t", "--buildType", choices = ['Release', 'Debug'], default='Release',
                        help="Value to be passed as CMAKE_BUILD_TYPE (default: Release)")
    parser.add_argument("-G", "--generator", help="Generator used to build projects. If none passed, using the one defined in file dependencies.json")
    parser.add_argument("--cmake", default="cmake", help="CMake executable")
    parser.add_argument("--graphicalAPI", default="OpenGL", help="Graphical API to be used for the compilation", choices=["OpenGL", "OpenGLES", "DirectX", "Vulkan", "RaspberryPi"])

    args = parser.parse_args()
    parseDependenciesJson(args)