#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tools/log.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    lError << "Error " << 41.5;
    lInfo << "Info " << 43.4f; 
    lRemember << "Remember " << true;
    lDebug << "Debug " << 42; 
    lWarning << "Warning " << 'i';
    return 0; 
}