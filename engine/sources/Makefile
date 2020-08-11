ENGINE_PATH ?=

CC ?=
CFLAGS ?=
INCLUDE := -I$(ENGINE_PATH)/sources -I$(ENGINE_PATH)/thirdparty/include
OUT := $(ENGINE_PATH)/out



.PHONY: all components core network physics platform render scenes servers ui utils

all: components core network physics platform render scenes servers ui utils $(OUT)/engine.o


components:
	@(cd components; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
core:
	@(cd core; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
network:
	@(cd network; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
physics:
	@(cd physics; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
platform:
	@(cd platform; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
render:
	@(cd render; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
scenes:
	@(cd scenes; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
servers:
	@(cd servers; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
ui:
	@(cd ui; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
utils:
	@(cd utils; $(MAKE) CC=$(CC) CFLAGS="$(CFLAGS)" ENGINE_PATH=$(ENGINE_PATH))
$(OUT)/engine.o: engine.cpp
	$(CC) $(CFLAGS) $(INCLUDE) engine.cpp -o $(OUT)/engine.o

