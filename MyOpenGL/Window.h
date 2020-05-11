#pragma once

struct GLFWwindow;


class Window
{
public:
	Window(int width, int height);
	~Window();

	//是否可用
	bool IsActive() { window_ != nullptr; }

	//是否将要关闭
	int IsShouldClose();

	//处理窗口输入
	void ProcessInput();

	//交换窗口缓冲,处理IO
	void SwapBuffer();

private:
	//窗口变化回调
	static void FramebufferSize_callback(GLFWwindow* window, int width, int height);

private:
	//glfw窗口
	GLFWwindow* window_;
};