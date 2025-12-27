#include "BlueCubeLayer.h"

BlueCubeLayer::BlueCubeLayer()
	: m_CameraController(1920 / 1080, true)
{
	CreateCube();
	CreateShader();

	m_CameraController.GetCamera().SetPosition({ 0.0f, 0.0f, 0.0f });
	m_CameraController.SetZoomLevel(1.5f);
}

BlueCubeLayer::~BlueCubeLayer()
{
}

void BlueCubeLayer::OnEvent(Render2D::Event& event)
{
	Render2D::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Render2D::WindowClosedEvent>([this](Render2D::WindowClosedEvent& event) { return OnWindowClosed(event); });
	dispatcher.Dispatch<Render2D::WindowResizedEvent>([this](Render2D::WindowResizedEvent& event) { return m_CameraController.OnWindowResized(event); });
	dispatcher.Dispatch<Render2D::MouseScrolledEvent>([this](Render2D::MouseScrolledEvent& event) { return m_CameraController.OnMouseScrolled(event); });
}

void BlueCubeLayer::OnUpdate(float deltaTime)
{
	m_CameraController.OnUpdate(deltaTime);

	m_CubeRotation += 45.0f * deltaTime;
	if (m_CubeRotation > 360.0f)
		m_CubeRotation -= 360.0f;
}

void BlueCubeLayer::OnRender()
{
	Render2D::Renderer::ClearScreen(0.1f, 0.1f, 0.1f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CubePosition);
	transform = glm::rotate(transform, glm::radians(m_CubeRotation), glm::vec3(0.3f, 1.0f, 0.5f));
	transform = glm::scale(transform, glm::vec3(1.0f));

	m_Shader->Bind();
	m_Shader->SetMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjection());
	m_Shader->SetMat4("u_Transform", transform);

	m_CubeVAO->Bind();
	Render2D::Renderer::DrawElements(m_CubeEBO->GetCount());
}

bool BlueCubeLayer::OnWindowClosed(Render2D::WindowClosedEvent& event)
{
	return false;
}

void BlueCubeLayer::CreateCube()
{
	float vertices[] = {
		// Front face (blue)
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,  // 0
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,  // 1
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,  // 2
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,  // 3

		// Back face (darker blue)
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.6f, 1.0f,  // 4
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.6f, 1.0f,  // 5
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.6f, 1.0f,  // 6
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.6f, 1.0f,  // 7

		// Top face (light blue)
		-0.5f,  0.5f, -0.5f,   0.3f, 0.3f, 1.0f, 1.0f,  // 8
		-0.5f,  0.5f,  0.5f,   0.3f, 0.3f, 1.0f, 1.0f,  // 9
		 0.5f,  0.5f,  0.5f,   0.3f, 0.3f, 1.0f, 1.0f,  // 10
		 0.5f,  0.5f, -0.5f,   0.3f, 0.3f, 1.0f, 1.0f,  // 11

		 // Bottom face (navy)
		 -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.4f, 1.0f,  // 12
		  0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.4f, 1.0f,  // 13
		  0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.4f, 1.0f,  // 14
		 -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.4f, 1.0f,  // 15

		 // Right face (medium blue)
		  0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 16
		  0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 17
		  0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 18
		  0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 19

		  // Left face (medium blue)
		  -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 20
		  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 21
		  -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.8f, 1.0f,  // 22
		  -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.8f, 1.0f   // 23
	};

	uint32_t indices[] = {
		// Front
		0, 1, 2,
		2, 3, 0,

		// Back
		4, 6, 5,
		6, 4, 7,

		// Top
		8, 9, 10,
		10, 11, 8,

		// Bottom
		12, 14, 13,
		14, 12, 15,

		// Right
		16, 17, 18,
		18, 19, 16,

		// Left
		20, 21, 22,
		22, 23, 20
	};

	m_CubeVAO = std::make_shared<Render2D::Renderer::VertexArray>();

	m_CubeVBO = std::make_shared<Render2D::Renderer::VertexBuffer>(vertices, sizeof(vertices));
	m_CubeVBO->SetLayout(
		{
			{ Render2D::Renderer::ShaderDataType::Float3, "a_Position" },
			{ Render2D::Renderer::ShaderDataType::Float4, "a_Color" }
		});

	m_CubeEBO = std::make_shared<Render2D::Renderer::ElementBuffer>(indices, 36);

	m_CubeVAO->AddVertexBuffer(m_CubeVBO);
	m_CubeVAO->AddElementBuffer(m_CubeEBO);

	LOG_INFO("Cube geometry created");
}

void BlueCubeLayer::CreateShader()
{
	m_Shader = std::make_shared<Render2D::Renderer::Shader>("shaders\\BlueCubeVertex.glsl", "shaders\\BlueCubeFragment.glsl");
	LOG_INFO("Shader created");
}
