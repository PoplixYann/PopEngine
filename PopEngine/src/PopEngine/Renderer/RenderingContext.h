#pragma once

namespace PE
{
	class RenderingContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}