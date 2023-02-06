#pragma once

#include "PopEngine/Core.h"

#include "PopEngine/Window.h"
#include "PopEngine/LayerStack.h"
#include "PopEngine/Events/Event.h"
#include "PopEngine/Events/ApplicationEvent.h"

#include "PopEngine/ImGui/ImGuiLayer.h"

#include "PopEngine/Core/Time.h"
#include "PopEngine/Core/Timestep.h"

namespace PE
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_TimeLastFrame;
	private:
		static Application* s_Instance; 
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

