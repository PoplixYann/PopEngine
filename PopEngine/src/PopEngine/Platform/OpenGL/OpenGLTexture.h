#pragma once

#include "PopEngine/Renderer/Texture.h"

namespace PE
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind(unsigned int slot = 0) const override;

		virtual int GetWidth() const override { return m_Width; }
		virtual int GetHeight() const override { return m_Height; }
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height;
	};
}