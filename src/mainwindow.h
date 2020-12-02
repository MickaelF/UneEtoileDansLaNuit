#pragma once

#include "basicinputs.h"

struct GLFWwindow;

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

    static void framebufferSizeCallback(GLFWwindow* window, int width,
                                        int height);

    int show();

private:
    GLFWwindow* m_window {nullptr};
    BasicInputs m_inputs;
};