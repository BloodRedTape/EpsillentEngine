#ifndef CONFIG
#define CONFIG

#define DEBUG_MODE
//#define PROFILING_MODE

#include "platform/platform.hpp"

#ifdef ENGINE_API_BUILD
	#define ENGINE_API ENGINE_API_EXPORT
#elif ENGINE_API_STATIC
	#define ENGINE_API
#else
	#define ENGINE_API ENGINE_API_IMPORT
#endif

#define DATAGRAM_DATA_SIZE 32

#endif