#include "pepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace PE
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// Initalize Glad with GLFW information
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PE_CORE_ASSERT(status, "Failed to initialize Glad !");

		PE_LOG_CORE_INFO("OpenGL Info :");
		PE_LOG_CORE_INFO("	Vendor : {0}", glGetString(GL_VENDOR));
		PE_LOG_CORE_INFO("	Renderer : {0}", glGetString(GL_RENDERER));
		PE_LOG_CORE_INFO("	Version : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}