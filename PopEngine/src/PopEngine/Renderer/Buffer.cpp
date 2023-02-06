#include "pepch.h"
#include "Buffer.h"

#include "PopEngine/Renderer/Renderer.h"

#include "PopEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace PE
{
	//////////////////////////////////////////////////////////////////////
	///// Vertex Buffer //////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	//////////////////////////////////////////////////////////////////////
	///// Index Buffer ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}