#pragma once

#include <vector>



class GLWindow;
class Mesh;
class Camera;
struct GLFWwindow;

class Viewer
{
public:
	Viewer(GLWindow* window);
	~Viewer();

	//��Ⱦ����
	void RenderScene(std::vector<Mesh*> meshes);

	//���ڱ仯�ص�
	static void framebufferSize_callback(GLFWwindow* window, int width, int height);

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	//��������
	void processInput();

public:
	static float lastX;
	static float lastY;
	static float deltaTime;
	static float lastFrame;

private:
	GLWindow* window_;
	int fps_;
};

