#pragma once

#include "PopEngine/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace PE
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}



/// Log macro take in parameter a string and every variable argument in the string
/// Exemple : PE_LOG_INFO("Hello World ! number is {0} and bool is {1}", 10, true)

// Log macro used for log of engine

#define PE_LOG_CORE_TRACE(...)			::PE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_LOG_CORE_INFO(...)			::PE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_LOG_CORE_WARN(...)			::PE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_LOG_CORE_ERROR(...)			::PE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_LOG_CORE_CRITICAL(...)		::PE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Log macro used for log of game

#define PE_LOG_TRACE(...)				::PE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_LOG_INFO(...)				::PE::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_LOG_WARN(...)				::PE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_LOG_ERROR(...)				::PE::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_LOG_CRITICAL(...)			::PE::Log::GetClientLogger()->critical(__VA_ARGS__)