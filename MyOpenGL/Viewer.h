#pragma once

class Window;


class Viewer
{
public :
	Viewer(Window* window);
	~Viewer();

	//‰÷»æ≥°æ∞
	void RenderScene();

private:
	Window* window_;
};