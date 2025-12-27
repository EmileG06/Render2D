#pragma once

#include <Render2D.h>

#include <memory>

class BlueCubeLayer : public Render2D::Layer
{
public:
	BlueCubeLayer();
	~BlueCubeLayer();

	virtual void OnEvent(Render2D::Event& event) override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	bool OnWindowClosed(Render2D::WindowClosedEvent& event);

private:
	void CreateCube();
	void CreateShader();

private:
	std::shared_ptr<Render2D::Renderer::VertexArray> m_CubeVAO;
	std::shared_ptr<Render2D::Renderer::VertexBuffer> m_CubeVBO;
	std::shared_ptr<Render2D::Renderer::ElementBuffer> m_CubeEBO;
	std::shared_ptr<Render2D::Renderer::Shader> m_Shader;

	Render2D::Renderer::OrthographicController m_CameraController;

	glm::vec3 m_CubePosition = { 0.0f, 0.0f, 0.0f };
	float m_CubeRotation = 0.0f;
};
