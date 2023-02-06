#include "pepch.h"
#include "RenderCommand.h"

#include "PopEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace PE
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}