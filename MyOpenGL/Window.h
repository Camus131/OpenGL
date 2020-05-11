#pragma once

struct GLFWwindow;


class Window
{
public:
	Window(int width, int height);
	~Window();

	//�Ƿ����
	bool IsActive() { window_ != nullptr; }

	//�Ƿ�Ҫ�ر�
	int IsShouldClose();

	//����������
	void ProcessInput();

	//�������ڻ���,����IO
	void SwapBuffer();

private:
	//���ڱ仯�ص�
	static void FramebufferSize_callback(GLFWwindow* window, int width, int height);

private:
	//glfw����
	GLFWwindow* window_;
};