#include "mainwindow.h"
#include <pttk/log.h>
#include <glad/glad.h>
// glad.h needs to be included before glfw3
#include <GLFW/glfw3.h>
#include "mesh.h"

MainWindow::MainWindow() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1600, 900, "LearnOpenGL", nullptr, nullptr);

    if (!m_window)
        throw std::runtime_error("Failed to create GLFW window");

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    lRemember << "Call to framebufferSizeCallback will be used to resize the viewport, once we use "
                 "ImGUI for engine UI";
    framebufferSizeCallback(m_window, 1600, 900);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    Mesh a;
}

MainWindow::~MainWindow()
{
    glfwTerminate();
}

void MainWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int MainWindow::show()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    return 0;
}
