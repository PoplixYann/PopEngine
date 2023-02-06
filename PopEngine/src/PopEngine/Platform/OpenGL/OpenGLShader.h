#pragma once

#include "PopEngine/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace PE
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;


		void SetUniformInt(const std::string& name, int value);
		void SetUniformInt2(const std::string& name, const glm::ivec2& value);
		void SetUniformInt3(const std::string& name, const glm::ivec3& value);
		void SetUniformInt4(const std::string& name, const glm::ivec4& value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& value);
		void SetUniformFloat3(const std::string& name, const glm::vec3& value);
		void SetUniformFloat4(const std::string& name, const glm::vec4& value);

		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string> shaderSources);
	private:
		uint32_t m_RendererID;
	};
}