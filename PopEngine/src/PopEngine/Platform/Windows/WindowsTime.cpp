#include "pepch.h"

#ifdef PE_PLATFORM_WINDOWS

#include "PopEngine/Core/Time.h"

#include <GLFW/glfw3.h>

namespace PE
{
	double Time::GetAppTime()
	{
		return glfwGetTime();
	}
}

#endif