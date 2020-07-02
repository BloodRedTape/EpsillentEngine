ENGINE_VERSION := 0
ENGINE_SUBVERSION := 5
ENGINE_PATCHLEVEL := 1

include game/ProjectConfig.mk

ENGINE_PATH := $(shell pwd)
SOURCES := $(shell find $(ENGINE_PATH) -name '*.cpp')
INCLUDE := -I./ -Ithirdparty/include -Igame

CC_LINUX := g++
CFLAGS_LINUX := -g -Werror -lstdc++ -lpthread -lX11 $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-graphics.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-window.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-audio.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-system.so $(ENGINE_PATH)/thirdparty/lib/linux/libsfml-network.so


CC_MACOS :=
CFLAGS_MACOS :=

all:
	$(error Specify your platform "make <platform name>" example: "make linux")
	


linux:
	@tput setaf 9
	@echo "+----------------------------------+"
	@echo "|                                  |"
	@echo "|        EpsEngine v$(ENGINE_VERSION).$(ENGINE_SUBVERSION).$(ENGINE_PATCHLEVEL)          |"
	@echo "|                                  |"
	@echo "|        by Epsillent inc.         |"
	@echo "+----------------------------------+"
	@tput sgr0
	@tput setaf 7;echo $(tput setaf 1)Compiling with ${CC_LINUX} compiler...;tput sgr0
	@$(CC_LINUX) $(SOURCES) $(CFLAGS_LINUX) $(INCLUDE) -o $(GAME_TITLE)-v$(GAME_VERSION).$(GAME_SUBVERSION).out	
	@tput setaf 10;echo $(tput setaf 1)Done!;tput sgr0
	@tput setaf 11;echo Executing...;tput sgr0
	@echo
	@./$(GAME_TITLE)-v$(GAME_VERSION).$(GAME_SUBVERSION).out
macos:
	$(info Building for macos)

clean:
	rm $(GAME_TITLE)-v$(GAME_VERSION).$(GAME_SUBVERSION).out
