#include "Viewer.h"
#include "Window.h"

#include "glad/glad.h"


Viewer::Viewer(Window* window)
{
	window_ = window;
}


Viewer::~Viewer()
{
}


void Viewer::RenderScene()
{
	if (!window_)
		return;

	while (!window_->IsShouldClose())
	{
		window_->ProcessInput();

		glClearColor(0.2f, 0.6f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






		window_->SwapBuffer();
	}
}


