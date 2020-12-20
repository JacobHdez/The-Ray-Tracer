#include "SandboxLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer()
	: m_CameraController(45.0f, 16.0f / 9.0f, 0.01f, 1000.f)
	, m_Model("assets/objects/backpack/backpack.obj")
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

	// ----- Test ----------
	m_Model.Setup();

	// ----- Z-Buffer ----------
	glEnable(GL_DEPTH_TEST); // Habilidad el test de profundidad
	glDepthFunc(GL_LESS); // Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/
	// -------------------------
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(m_Shader->GetRendererID());
	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_LightColor");
	glUniform3fv(location, 1, glm::value_ptr(m_Light.GetColor()));
	//glUniform3f(location, 1.0f, 0.5f, 0.31f);
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	// ---------------------
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

	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_Shader->GetRendererID());

	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));

	// ----- Test ----------
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ObjectColor");
	glUniform3f(location, 0.25f, 0.25f, 0.25f);
	m_Model.Draw(m_Shader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ObjectColor");
	glUniform3f(location, 0.1f, 0.1f, 0.1f);
	m_Model.Draw(m_Shader);
	// ---------------------
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Hierachy");
	if (ImGui::TreeNode("Render"))
	{
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