#include "pepch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace PE
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Set pattern for every log message (exemple here : "[HOURS:MINUTES:SECONDES] LOGGERNAME: TEXT")
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Create new logger which is console color logger and named "POPENGINE", assign it to s_CoreLogger
		s_CoreLogger = spdlog::stdout_color_mt("PE");
		// Set level of default log to trace for s_CoreLogger
		s_CoreLogger->set_level(spdlog::level::trace);

		// Create new logger which is console color logger and named "APP", assign it to s_ClientLogger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}