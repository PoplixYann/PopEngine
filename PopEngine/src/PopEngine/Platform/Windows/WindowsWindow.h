#pragma once

#include "PopEngine/Window.h"

struct GLFWwindow;

namespace PE
{
	class RenderingContext;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& _props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& _callback) override { m_Data.EventCallback = _callback; }
		void SetVSync(bool _enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& _props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		RenderingContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}