#pragma once

#include <memory>

#ifdef PH_PLATFORM_WINDOWS
	#ifdef PH_DINAMIC_BUILD
		#ifdef PH_BUILD_DLL
			#define PH_API __declspec(dllexport)
		#else
			#define PH_API __declspec(dllimport)
		#endif
	#else
		#define PH_API
	#endif // PH_DINAMIC_BUILD
#else
	#error Phoenix supports only Windows!
#endif // PH_PLATFORM_WINDOWS

#ifdef PH_DEBUG
	#define PH_ENABLE_ASSERTS
#endif // PH_DEBUG


#ifdef PH_ENABLE_ASSERTS
	#define PH_CORE_ASSERT(x, ...) if(!(x)) {PH_CORE_ERROR(__VA_ARGS__); __debugbreak();}
	#define PH_ASSERT(x, ...) if(!(x)) {PH_ERROR(__VA_ARGS__); __debugbreak();}
#else
	#define PH_CORE_ASSERT(x, ...)
	#define PH_ASSERT(x, ...)
#endif // PH_ENABLE_ASSERTS


#define BIT(x) (1 << x)
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T>
using Scope = std::unique_ptr<T>;