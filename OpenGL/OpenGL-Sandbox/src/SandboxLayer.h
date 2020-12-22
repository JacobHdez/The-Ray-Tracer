#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include "MyCore.h"

class SandboxLayer : public GLCore::Layer
{
public:
	SandboxLayer(const std::string& filepath);
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	bool OnWindowResized(GLCore::WindowResizeEvent& e);

	void TakeScreenShot();
	void Render();
private:
	GLCore::Utils::PerspectiveCameraController m_CameraController;
	GLCore::Utils::Shader* m_Shader;

	Scene m_Scene;

	unsigned int m_Width = { 1280 };
	unsigned int m_Height = { 720 };

	std::string m_ImageFilename = "SceneRT";
	int m_ImageWidth = { 80 };
	int m_ImageHeight = { 45 };
};