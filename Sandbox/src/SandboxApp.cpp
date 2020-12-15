#include <OpenGL_Core.h>

class Sandbox : public OpenGL_Core::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

OpenGL_Core::Application* OpenGL_Core::CreateApplication()
{
	return new Sandbox();
}