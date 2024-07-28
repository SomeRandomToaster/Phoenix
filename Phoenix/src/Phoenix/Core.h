#pragma once

#ifdef PH_PLATFORM_WINDOWS
	#ifdef PH_BUILD_DLL
		#define PH_API __declspec(dllexport)
	#else
		#define PH_API __declspec(dllimport)
	#endif
#else
	#error Phoenix supports only Windows!
#endif // PH_PLATFORM_WINDOWS
