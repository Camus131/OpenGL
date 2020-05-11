#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


Window::Window(int width, int height)
{
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
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, FramebufferSize_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "初始化glad失败！" << std::endl;
        glfwTerminate();
        window_ = nullptr;
    }
}


Window::~Window()
{
    if (window_)
    {
        glfwTerminate();
        window_ = nullptr;
    }
}

int Window::IsShouldClose()
{
    return glfwWindowShouldClose(window_);
}


void Window::ProcessInput()
{
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);
}


void Window::SwapBuffer()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}


void Window::FramebufferSize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}