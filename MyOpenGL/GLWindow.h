#pragma once

struct GLFWwindow;



class GLWindow
{
public:
	GLWindow(int width, int height);
	~GLWindow();

	//是否可用
	bool IsActive()const { return window_ != nullptr; }

	//窗口宽
	int Width()const { return width_; }

	//窗口高
	int Height()const { return height_; }

	//是否将要关闭
	int IsShouldClose();

	//交换窗口缓冲,处理IO
	void SwapBuffer();

	//获得窗口
	GLFWwindow* GetWindow() { return window_; }

private:
	//glfw窗口
	GLFWwindow* window_;

	int width_;

	int height_;
};