#include "SandboxLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer(const std::string& filepath)
	: m_CameraController{ 45.0f, 16.0f / 9.0f, 0.01f, 1000.0f }, m_Shader{ nullptr }, m_Scene{ filepath }
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	EnableGLDebugging();

	m_Shader = Shader::FromGLSLTextFiles(
		"assets/shaders/basic.vert.glsl",
		"assets/shaders/basic.frag.glsl"
	);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Scene.Setup();
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
}

void SandboxLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(SandboxLayer::OnWindowResized));

	m_CameraController.OnEvent(event);
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	glClearColor(0.75f, 0.75f, 0.75f, 0.75f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_Shader->GetRendererID());

	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_LightColor");
	glUniform3f(location, 1.0f, 1.0f, 1.0f);
	
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ObjectColor");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3f(location, 0.25f, 0.25f, 0.25f);
	m_Scene.Draw(m_Shader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniform3f(location, 0.1f, 0.1f, 0.1f);
	m_Scene.Draw(m_Shader);
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Hierachy");
	if (ImGui::TreeNode("Render"))
	{
		ImGui::Text(m_ImageFilename.c_str());
		ImGui::InputInt("Width", &m_ImageWidth);
		ImGui::InputInt("Height", &m_ImageHeight);
		if (ImGui::Button("Render"))
		{
			LOG_INFO("Starting to render!");
			//Render();
			RTRender(m_Scene, m_ImageWidth, m_ImageHeight, m_ImageFilename);
			LOG_INFO("The rendering is over!");
		}
		ImGui::TreePop();
	}
	if (ImGui::Button("Screenshot"))
	{
		LOG_INFO("Taking screenshot...");
		SandboxLayer::TakeScreenShot();
		LOG_INFO("Screenshot taken.");
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

bool SandboxLayer::OnWindowResized(WindowResizeEvent& e)
{
	m_Width = (unsigned int)e.GetWidth();
	m_Height = (unsigned int)e.GetHeight();
	glViewport(0, 0, m_Width, m_Height);
	return false;
}

void SandboxLayer::TakeScreenShot()
{
	unsigned char* pixels = new unsigned char[3 * m_Width * m_Height];
	glReadPixels(0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	stbi_write_png("outputs/screenshot.png", m_Width, m_Height, 3, pixels, 3 * m_Width * sizeof(unsigned char));
	delete[] pixels;
}

void SandboxLayer::Render()
{
	float nPixels = (float)(m_ImageWidth * m_ImageHeight);
	unsigned int count = 0;
	std::string buff;

	unsigned char* pixels = new unsigned char[3 * m_ImageWidth * m_ImageHeight];
	for (unsigned int i = 0; i < m_ImageHeight; ++i)
	{
		for (unsigned int j = 0; j < m_ImageWidth; ++j)
		{
			if (count % 1000 == 0)
			{
				buff = Convert(count / nPixels * 100.0f) + "%";
				LOG_INFO(buff.c_str());
			}
			count++;

			// Test img
			pixels[0 + 3 * (j + m_ImageWidth * i)] = ((float)i / (float)m_ImageHeight) * 255;
			pixels[1 + 3 * (j + m_ImageWidth * i)] = ((float)j / (float)m_ImageWidth) * 255;
			pixels[2 + 3 * (j + m_ImageWidth * i)] = ((i < m_ImageHeight / 2.0f) && (j < m_ImageWidth / 2.0f) ||
						                              (i >= m_ImageHeight / 2.0f) && (j >= m_ImageWidth / 2.0f)) ? 255 : 0;
		}
	}
	std::string imagePath = "outputs/" + m_ImageFilename + ".png";
	stbi_write_png(imagePath.c_str(), m_ImageWidth, m_ImageHeight, 3, pixels, 3 * m_ImageWidth * sizeof(unsigned char));
	delete[] pixels;

	buff = Convert(count / nPixels * 100.0f) + "%";
	LOG_INFO(buff.c_str());
}