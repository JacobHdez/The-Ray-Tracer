#include "SandboxLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer()
	: m_CameraController(45.0f, 16.0f / 9.0f, 0.01f, 1000.f)
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	EnableGLDebugging();

	m_Shader = Shader::FromGLSLTextFiles(
		"assets/shaders/shader.vert.glsl",
		"assets/shaders/shader.frag.glsl"
	);

	// ----- Test ----------

	// ----- Z-Buffer ----------
	glEnable(GL_DEPTH_TEST); // Habilidad el test de profundidad
	glDepthFunc(GL_LESS); // Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	// -------------------------

	float positions[] = {
		// Positions          // Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		 0,  1,  2,
		 3,  4,  5,
		 6,  7,  8,
		 9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};

	va.Setup();
	vb.Setup(positions, 36 * 6 * sizeof(float));
	layout.Push<float>(3); // positions
	layout.Push<float>(3); // normals
	// layout.Push<float>(2); // texture coords
	va.AddBuffer(vb, layout);

	// ...

	ib.Setup(indices, 12 * 3);

	Material m_Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);


	glUseProgram(m_Shader->GetRendererID());
	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_LightColor");
	glUniform3fv(location, 1, glm::value_ptr(m_Light.GetColor()));
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_LightPos");
	glUniform3fv(location, 1, glm::value_ptr(m_Light.GetPosition()));
	/*location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ObjectColor");
	glUniform3f(location, 1.0f, 0.5f, 0.31f);*/
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	m_Material.SendToShader(m_Shader);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_Shader->GetRendererID());

	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));
	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_CameraPos");
	glUniform3fv(location, 1, glm::value_ptr(m_CameraController.GetCamera().GetPosition()));

	// ----- Test ----------
	// glBindTexture(GL_TEXTURE_2D, texture);
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
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