#pragma once

class Window;


class Viewer
{
public :
	Viewer(Window* window);
	~Viewer();

	//��Ⱦ����
	void RenderScene();

private:
	Window* window_;
};