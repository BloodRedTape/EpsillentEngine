CC := g++
CFLAGS := -g -Werror -lstdc++ -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system

SOURCES:= $(shell find $(Engine/src/) -name '*.cpp')
INCLUDE := -I./ -IGame

all:
	@tput setaf 9
	@echo "+----------------------------------+"
	@echo "|                                  |"
	@echo "|            EpsEngine             |"
	@echo "|                                  |"
	@echo "|        by Epsillent inc.         |"
	@echo "+----------------------------------+"
	@tput sgr0
	@tput setaf 7;echo $(tput setaf 1)Compiling with ${CC} compiler...;tput sgr0
	@$(CC) $(SOURCES) $(CFLAGS) $(INCLUDE) -o EPS.out	
	@tput setaf 10;echo $(tput setaf 1)Done!;tput sgr0
	@tput setaf 11;echo Executing...;tput sgr0
	@echo
	@./EPS.out
	


clean:
	rm EPS.out
