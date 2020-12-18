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

	// ----- Test ----------

	// ----- Z-Buffer ----------
	glEnable(GL_DEPTH_TEST); // Habilidad el test de profundidad
	glDepthFunc(GL_LESS); // Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	// -------------------------
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Shader = Shader::FromGLSLTextFiles(
		"assets/shaders/basic2.vert.glsl",
		"assets/shaders/basic2.frag.glsl"
	);

	float positions[] = {
		// Positions      // Colors         // TexCoords
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		5, 6, 7,
		0, 1, 5,
		4, 5, 0,
		0, 2, 6,
		0, 4, 6,
		1, 3, 5,
		3, 7, 5,
		2, 3, 6,
		3, 6, 7
	};

	/*// ----- Textures ----------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("assets/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// -------------------------*/

	va.Setup();
	vb.Setup(positions, 8 * 6 * sizeof(float));
	layout.Push<float>(3); // positions
	layout.Push<float>(3); // colors
	// layout.Push<float>(2); // texture coords
	va.AddBuffer(vb, layout);

	// ...

	ib.Setup(indices, 12 * 3);

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
	m_CameraController.OnEvent(event);
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_Shader->GetRendererID());

	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));

	// glBindTexture(GL_TEXTURE_2D, texture);
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Hierachy");
	if (ImGui::Button("Screenshot"))
	{
		LOG_INFO("Taking screenshot...");
		unsigned char* pixels = new unsigned char[3 * 1280 * 720];
		glReadPixels(0, 0, 1280, 720, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		stbi_write_png("ss.png", 1280, 720, 3, pixels, 3 * 1280 * sizeof(unsigned char));
		delete[] pixels;
		LOG_INFO("Screenshot taken.");
	}
	ImGui::End();
}
