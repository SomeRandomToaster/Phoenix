#include "pch.h"
#include "Log.h"

namespace Phoenix {

	Ref<spdlog::logger> Log::coreLogger;
	Ref<spdlog::logger> Log::clientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("PHOENIX");
		coreLogger->set_level(spdlog::level::level_enum::trace);

		clientLogger = spdlog::stdout_color_mt("APP");
		clientLogger->set_level(spdlog::level::level_enum::trace);
	}
}