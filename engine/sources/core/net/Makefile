ENGINE_PATH ?=

CC ?=
CFLAGS ?=
INCLUDE := -I$(ENGINE_PATH)/sources -I$(ENGINE_PATH)/thirdparty/include
OUT := $(ENGINE_PATH)/out

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

.PHONY: all

all: $(OBJ)

%.o: %.cpp 
	$(MAKE) $(ENGINE_PATH)/out/$*.o 

$(ENGINE_PATH)/out/%.o: %.cpp
	$(CC) $(INCLUDE) $(CFLAGS) $*.cpp -o $(ENGINE_PATH)/out/$*.o