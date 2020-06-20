#include "engine/platform/platform.hpp"

#ifdef PLATFORM_LINUX
    #include "X11/Xlib.h"
#endif


void Platform::init(){
    #ifdef PLATFORM_LINUX
        XInitThreads();
    #endif
}
