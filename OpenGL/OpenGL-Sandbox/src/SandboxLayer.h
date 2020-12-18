#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include "MyCore/MyCore.h"

class SandboxLayer : public GLCore::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	// ----- Test ----------
	GLCore::Utils::Shader* m_Shader;
	GLCore::Utils::PerspectiveCameraController m_CameraController;

	unsigned int texture;
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	// ---------------------
};