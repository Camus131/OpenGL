#include "Viewer.h"
#include "GLWindow.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "RenderState.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <ctime>
#include <iostream>


Viewer::Viewer(GLWindow* window)
{
	window_ = window;
	fps_ = 0;
}


Viewer::~Viewer()
{
}


void Viewer::RenderScene(std::vector<Mesh*> meshes)
{
	if (!window_)
		return;

	glfwSetFramebufferSizeCallback(window_->GetWindow(), framebufferSize_callback);
	glfwSetCursorPosCallback(window_->GetWindow(), mouse_callback);
	glfwSetScrollCallback(window_->GetWindow(), scroll_callback);

	//glViewport(0, 0, window_->Width(), window_->Height());

	glEnable(GL_DEPTH_TEST);

	clock_t start, end;

	while (!window_->IsShouldClose())
	{
		start = clock();
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();

		glClearColor(0.2f, 0.6f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto it = meshes.begin();it != meshes.end();++it)
		{
			ShaderProgram* shader_program = (*it)->GetState()->GetShaderProgram();
			shader_program->Use();
			shader_program->SetUniformMat4x4("model", (*it)->GetModelMatrix());
			shader_program->SetUniformMat4x4("view", Camera::DeFaultCamera.GetViewMatrix());
			shader_program->SetUniformMat4x4("projection", Matrix4x4f::PerspectiveFov(Camera::DeFaultCamera.GetFov(), (float)window_->Width() / (float)window_->Height(), 0.1f, 100.0f));
			shader_program->SetUniformVec3("viewPos", Camera::DeFaultCamera.GetPosition());
			shader_program->SetUniformVec3("light.position", Vector3f(2.0f, 2.0f, 2.0f));
			shader_program->SetUniformVec3("light.ambient", Vector3f(0.2f, 0.2f, 0.2f));
			shader_program->SetUniformVec3("light.diffuse", Vector3f(0.8f, 0.8f, 0.8f));
			shader_program->SetUniformVec3("light.specular", Vector3f(1.0f, 1.0f, 1.0f));
			shader_program->SetUniformFloat("material.shininess", 64.0f);
			shader_program->SetUniformInt("material.diffuse", 0);
			shader_program->SetUniformInt("material.specular", 1);
			(*it)->Draw();
		}

		window_->SwapBuffer();
		end = clock();
		clock_t time = end - start;
		if (time)
			fps_ = 1000 / time;
		std::cout << fps_ << std::endl;
	}
}


void Viewer::framebufferSize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void Viewer::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xposf = (float)xpos;
	float yposf = (float)ypos;

	float xoffset = lastX - xposf;
	float yoffset = lastY - yposf;

	lastX = xposf;
	lastY = yposf;

	Camera::DeFaultCamera.Turn(xoffset, yoffset);
}


void Viewer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::DeFaultCamera.Zoom(-(float)yoffset);
}


void Viewer::processInput()
{
	if (glfwGetKey(window_->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window_->GetWindow(), true);

	if (glfwGetKey(window_->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		Camera::DeFaultCamera.Move(FORWARD, deltaTime);
	if (glfwGetKey(window_->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		Camera::DeFaultCamera.Move(BACKWARD, deltaTime);
	if (glfwGetKey(window_->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		Camera::DeFaultCamera.Move(LEFT, deltaTime);
	if (glfwGetKey(window_->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		Camera::DeFaultCamera.Move(RIGHT, deltaTime);
}

float Viewer::lastX = 1280 / 2.0f;
float Viewer::lastY = 720 / 2.0f;
float Viewer::deltaTime = 0.0f;
float Viewer::lastFrame = 0.0f;