#pragma once

#include "pepch.h"

#include "PopEngine/Core.h"
#include "PopEngine/Events/Event.h"

namespace PE
{
	// Basics window data
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Pop Engine",
					unsigned int width = 1280,
					unsigned int height = 720) :
			Title(title), Width(width), Height(height)
		{}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		// This static method will be defined in the right context to return the wish window
		// Exemple : We used a GLFW window we gonna define this function to return a new GLFW window
		static Window* Create(const WindowProps& props = WindowProps());
	};
}