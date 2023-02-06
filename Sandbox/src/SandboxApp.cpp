#include <PopEngine.h>

#include <PopEngine/Platform/OpenGL/OpenGLShader.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderLayer : public PE::Layer
{
public:
	RenderLayer() :
		Layer("Render"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f)
	{
		m_SquareVA.reset(PE::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};
		PE::Ref<PE::VertexBuffer> squareVB(PE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{PE::ShaderDataType::Float3, "a_Position"},
			{PE::ShaderDataType::Float2, "a_TexCoord"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[3 * 2] = {
			0, 1, 2,
			2, 3, 0,
		};
		PE::Ref<PE::IndexBuffer> squareIB(PE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			uniform vec3 u_Color;

			void main()
			{
				o_Color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(PE::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


		m_TextureShader.reset(PE::Shader::Create("Assets/shaders/Texture.glsl"));

		m_Texture = PE::Texture2D::Create("Assets/textures/cat.jpg");

		m_TextureShader->Bind();
		std::dynamic_pointer_cast<PE::OpenGLShader>(m_TextureShader)->SetUniformInt("u_Texture", 0);
	}

	void OnAttach() override
	{

	}

	void OnDetach() override
	{

	}

	void OnUpdate(PE::Timestep ts) override
	{
		m_LastFrameTimestep = ts;

		if (PE::Input::IsKeyPressed(PE_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		if (PE::Input::IsKeyPressed(PE_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (PE::Input::IsKeyPressed(PE_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		if (PE::Input::IsKeyPressed(PE_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (PE::Input::IsKeyPressed(PE_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (PE::Input::IsKeyPressed(PE_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		PE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		PE::RenderCommand::Clear();

		PE::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 1.0f));

		m_FlatColorShader->Bind();
		std::dynamic_pointer_cast<PE::OpenGLShader>(m_FlatColorShader)->SetUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				PE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		glm::vec3 texturedSquarePos(1.0f, 1.0f, 0.0f);
		glm::mat4 texturedSquareTransform = glm::translate(glm::mat4(1.0f), texturedSquarePos);
		PE::Renderer::Submit(m_TextureShader, m_SquareVA, texturedSquareTransform);

		PE::Renderer::EndScene();
	}

	void OnEvent(PE::Event& event) override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("FrameRate");
		ImGui::Text("FPS : %.1f", 1.0f / m_LastFrameTimestep);
		ImGui::End();

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::BeginChild("Shader");
		ImGui::Text("Shader Settings");
		ImGui::Text("Texture Shader");
		ImGui::SameLine();
		if (ImGui::Button("Recompile"))
		{
			m_TextureShader.reset(PE::Shader::Create("Assets/shaders/Texture.glsl"));
		}
		ImGui::EndChild();

		ImGui::End();
	}

private:
	PE::Timestep m_LastFrameTimestep;

	PE::Ref<PE::Shader> m_FlatColorShader, m_TextureShader;
	PE::Ref<PE::VertexArray> m_SquareVA;
	PE::Ref<PE::Texture> m_Texture;

	PE::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public PE::Application
{
public:
	Sandbox()
	{
		PushLayer(new RenderLayer());
	}

	~Sandbox() {}
};

PE::Application* PE::CreateApplication()
{
	return new Sandbox();
}