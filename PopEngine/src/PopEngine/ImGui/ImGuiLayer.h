#pragma once

#include "PopEngine/Core.h"
#include "PopEngine/Base.h"
#include "PopEngine/Layer.h"

namespace PE
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}