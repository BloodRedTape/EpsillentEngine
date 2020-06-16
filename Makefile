CC_LINUX := g++
CFLAGS_LINUX := -g -Werror -lstdc++ -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
SOURCES_LINUX := $(shell find $(Engine/src/) -name '*.cpp')
INCLUDE_LIXUX := -I./ -IGame

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
	@tput setaf 7;echo $(tput setaf 1)Compiling with ${CC} compiler...;tput sgr0
	@$(CC_LINUX) $(SOURCES_LINUX) $(CFLAGS_LINUX) $(INCLUDE_LINUX) -o EPS.out	
	@tput setaf 10;echo $(tput setaf 1)Done!;tput sgr0
	@tput setaf 11;echo Executing...;tput sgr0
	@echo
	@./EPS.out
macos:
	$(info Building for macos)

clean:
	rm EPS.out
