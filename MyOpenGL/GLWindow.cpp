#include "GLWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>



GLWindow::GLWindow(int width, int height)
{
    width_ = 0;
    height_ = 0;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width, height, "OpenGL3.3", nullptr, nullptr);
    if (!window_)
    {
        std::cout << "创建glfw窗口失败！" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "初始化glad失败！" << std::endl;
        glfwTerminate();
        window_ = nullptr;
        return;
    }
    width_ = width;
    height_ = height;
}


GLWindow::~GLWindow()
{
    if (window_)
    {
        glfwTerminate();
        window_ = nullptr;
    }
}

int GLWindow::IsShouldClose()
{
    return glfwWindowShouldClose(window_);
}


void GLWindow::SwapBuffer()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}