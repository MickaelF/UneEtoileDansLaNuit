#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tools/log.h"
#include <memory>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(1600, 900, "LearnOpenGL", nullptr, nullptr);
    if (!window)
    {
        lFatal << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        lFatal << "Failed to initialize GLAD";
        return -1;
    }
    lRemember << "Call to framebufferSizeCallback will be used to resize the viewport, once we use ImGUI for engine UI"; 
    framebufferSizeCallback(window, 1600, 900); 
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0; 
}
