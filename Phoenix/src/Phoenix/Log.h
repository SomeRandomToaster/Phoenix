#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Phoenix {
	class PH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};

	
}

#define PH_CORE_CRITICAL(...) ::Phoenix::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define PH_CORE_ERROR(...) ::Phoenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PH_CORE_WARN(...) ::Phoenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PH_CORE_INFO(...) ::Phoenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PH_CORE_TRACE(...) ::Phoenix::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define PH_CRITICAL(...) ::Phoenix::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define PH_ERROR(...) ::Phoenix::Log::GetClientLogger()->error(__VA_ARGS__)
#define PH_WARN(...) ::Phoenix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PH_INFO(...) ::Phoenix::Log::GetClientLogger()->info(__VA_ARGS__)
#define PH_TRACE(...) ::Phoenix::Log::GetClientLogger()->trace(__VA_ARGS__)