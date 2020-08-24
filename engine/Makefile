ENGINE_VERSION := 0
ENGINE_SUBVERSION := 8
ENGINE_PATCHLEVEL := 3



ENGINE_PATH := $(shell pwd)
SOURCES := $(shell find $(ENGINE_PATH) -name '*.cpp')
INCLUDE := -I$(ENGINE_PATH)/sources -I$(ENGINE_PATH)/thirdparty/include


CC_LINUX := clang
CC_FLAGS_LINUX := -Werror -c -fPIC -std=c++11 
LD_FLAGS_LINUX := -shared -lpthread -lX11 -lm -lstdc++
LD_LINUX := ld

CC_MACOS := g++
CFLAGS_MACOS := -dynamiclib -std=c++11 
LINKER_MACOS := $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-graphics.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-system.dylib /$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-window.dylib /$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-network.dylib


.PHONY: all Linux Darwin
PLATFORM := $(shell uname -s)




all:
	@tput setaf 9
	@echo "+----------------------------------+"
	@echo "|                                  |"
	@echo "|        EpsEngine v$(ENGINE_VERSION).$(ENGINE_SUBVERSION).$(ENGINE_PATCHLEVEL)          |"
	@echo "|                                  |"
	@echo "|        by Epsillent inc.         |"
	@echo "+----------------------------------+"
	@tput sgr0
	@echo
	$(info [ENGINE-v$(ENGINE_VERSION).$(ENGINE_SUBVERSION).$(ENGINE_PATCHLEVEL)]: compiling for $(PLATFORM))
	@mkdir -p out
	@$(MAKE) $(PLATFORM)

Darwin:
	@rm -f libengine.dylib
	@$(CC_MACOS) $(CFLAGS_MACOS) $(INCLUDE) $(SOURCES) $(LINKER_MACOS) -o libengine.dylib 
Linux:
	@rm -f libengine.so
	@(cd sources; $(MAKE) CC=$(CC_LINUX) CFLAGS="$(CC_FLAGS_LINUX)" ENGINE_PATH=$(ENGINE_PATH)) 
	@$(CC_LINUX) $(LD_FLAGS_LINUX) out/*.o -o libengine.so
clean:
	@rm -f libengine.*
	@rm -fr out


