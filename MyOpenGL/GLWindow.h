#pragma once

struct GLFWwindow;



class GLWindow
{
public:
	GLWindow(int width, int height);
	~GLWindow();

	//�Ƿ����
	bool IsActive()const { return window_ != nullptr; }

	//���ڿ�
	int Width()const { return width_; }

	//���ڸ�
	int Height()const { return height_; }

	//�Ƿ�Ҫ�ر�
	int IsShouldClose();

	//�������ڻ���,����IO
	void SwapBuffer();

	//��ô���
	GLFWwindow* GetWindow() { return window_; }

private:
	//glfw����
	GLFWwindow* window_;

	int width_;

	int height_;
};