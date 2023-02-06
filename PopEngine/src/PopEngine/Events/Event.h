#pragma once

#include "pepch.h"

#include "PopEngine/Core.h"
#include "PopEngine/Base.h"


namespace PE
{
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	// This define is used to create and define those 3 functions in an Event inherit class
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// This define is used to create and define GetCategoryFlags() function in an Event inherit class
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// Check if event is in specific category
		inline bool IsInCategory(EventCategory _category)
		{
			return GetCategoryFlags() & _category;
		}
	};

	// EventDispatcher is create and use for dispatch an event on others callbacks
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// Dispatch is call for dispatch this event on one other callback
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// Check if callback wanted event type is same of this event type
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// The operator |= is used for bitwise OR
				// a bool in binary => false = 0 and true = 1
				// i.e (false(0) |= true(1) => true(1))
				// _func return a bool
				// if m_Event.Handled is false(0) and _func return true(1) => m_Event.Handled = true(1)
				// if m_Event.Handled is true(1) and _func return false(0) => m_Event.Handled = true(1)
				// if both is false(0) => m.Event.Handled = false(0)
				// if both is true(1) => m.Event.Handled = true(1)
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return (os << e.ToString());
	}

}