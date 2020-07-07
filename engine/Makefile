ENGINE_VERSION := 0
ENGINE_SUBVERSION := 6
ENGINE_PATCHLEVEL := 4



ENGINE_PATH := $(shell pwd)
SOURCES := $(shell find $(ENGINE_PATH) -name '*.cpp')
INCLUDE := -I$(ENGINE_PATH)/sources -I$(ENGINE_PATH)/thirdparty/include


CC_LINUX := g++
CFLAGS_LINUX := -Werror -shared -fPIC -lpthread -lstdc++ -lX11

CC_MACOS := g++
CFLAGS_MACOS := -dynamiclib -std=c++11 
LINKER_MACOS := $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-graphics.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-system.dylib /$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-window.dylib


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
	@$(MAKE) $(PLATFORM)

Darwin:
	@rm -f libengine.dylib
	@$(CC_MACOS) $(CFLAGS_MACOS) $(INCLUDE) $(SOURCES) $(LINKER_MACOS) -o libengine.dylib 
Linux:
	@rm -f libengine.so
	@$(CC_LINUX) $(CFLAGS_LINUX) $(INCLUDE) $(SOURCES) -o libengine.so

clean:
	@rm -f libengine.*


