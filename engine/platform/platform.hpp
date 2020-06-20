#ifndef INIT_H
#define INIT_H


#ifdef WIN32
    #define PLATFORM_WINDOWS
#elif __APPLE__
    #define PLATFROM_MACOS
#elif __linux__
    #define PLATFORM_LINUX
#else
    #define PLATFORM_UNKNOWN
#endif


class Platform{
public:
    static void init();
};

#endif