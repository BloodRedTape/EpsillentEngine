CC_LINUX := g++
ENGINE_PATH := $(shell pwd)
CFLAGS_LINUX := -g -Werror -lstdc++ $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-graphics.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-window.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-audio.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-system.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-network.so
SOURCES_LINUX := $(shell find $(ENGINE_PATH) -name '*.cpp')
INCLUDE_LINUX := -I./ -Ithirdparty/include -Igame

CC_MACOS :=
CFLAGS_MACOS :=
SOURCES_MACOS :=
INCLUDE_MACOS :=

all:
	$(error Specify your platform "make <platform name>" example: "make linux")
	


linux:
	@tput setaf 9
	@echo "+----------------------------------+"
	@echo "|                                  |"
	@echo "|            EpsEngine             |"
	@echo "|                                  |"
	@echo "|        by Epsillent inc.         |"
	@echo "+----------------------------------+"
	@tput sgr0
	@tput setaf 7;echo $(tput setaf 1)Compiling with ${CC_LINUX} compiler...;tput sgr0
	@$(CC_LINUX) $(SOURCES_LINUX) $(CFLAGS_LINUX) $(INCLUDE_LINUX) -o EPS.out	
	@tput setaf 10;echo $(tput setaf 1)Done!;tput sgr0
	@tput setaf 11;echo Executing...;tput sgr0
	@echo
	@./EPS.out
macos:
	$(info Building for macos)

clean:
	rm EPS.out
