#pragma once

#include "PopEngine/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace PE
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}