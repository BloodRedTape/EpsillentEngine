#ifndef INIT_H
#define INIT_H


#ifdef _WIN64
    #define PLATFORM_WINDOWS
#elif __APPLE__
    #define PLATFROM_MACOS
#elif __linux__
    #define PLATFORM_LINUX
#else
    #define PLATFORM_UNKNOWN
#endif


#if defined(PLATFORM_WINDOWS)

    // Windows compilers need specific (and different) keywords for export and import
    #define ENGINE_API_EXPORT __declspec(dllexport)
    #define ENGINE_API_IMPORT __declspec(dllimport)

    // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
    #ifdef _MSC_VER

        #pragma warning(disable: 4251)

    #endif

#else // Linux, FreeBSD, Mac OS X

    #if __GNUC__ >= 4

        // GCC 4 has special keywords for showing/hidding symbols,
        // the same keyword is used for both importing and exporting
        #define ENGINE_API_EXPORT __attribute__ ((__visibility__ ("default")))
        #define ENGINE_API_IMPORT __attribute__ ((__visibility__ ("default")))

    #else

        // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
        #define ENGINE_API_EXPORT
        #define ENGINE_API_IMPORT

    #endif

#endif

class Platform{
public:
    static void init();
};

#endif