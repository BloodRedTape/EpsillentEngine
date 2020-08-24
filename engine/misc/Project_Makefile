ENGINE_PATH := ../../engine
INCLUDE := -I$(ENGINE_PATH)/sources/ -I$(ENGINE_PATH)/thirdparty/include -I./sources


CC_LINUX := clang
CFLAGS_LINUX := -Werror -std=c++11
LINKER_FLAGS_LINUX := -lX11 -lstdc++ -lm -lpthread
LINKER_FLAGS_LINUX_BUILD := $(LINKER_FLAGS_LINUX) -Wl,-R$(ENGINE_PATH)/thirdparty/lib/Linux $(ENGINE_PATH)/libengine.so $(ENGINE_PATH)/thirdparty/lib/Linux/libsfml-audio.so $(ENGINE_PATH)/thirdparty/lib/Linux/libsfml-window.so $(ENGINE_PATH)/thirdparty/lib/Linux/libsfml-graphics.so $(ENGINE_PATH)/thirdparty/lib/Linux/libsfml-system.so $(ENGINE_PATH)/thirdparty/lib/Linux/libsfml-network.so
LINKER_FLAGS_LINUX_DISTRIBUTION := $(LINKER_FLAGS_LINUX) -Llibs -Wl,-R./libs -lengine -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -lsfml-audio

CC_DARWIN := g++
CFLAGS_DARWIN := -std=c++11 -headerpad_max_install_names
LINKER_FLAGS_DARWIN_BUILD := $(ENGINE_PATH)/libengine.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-graphics.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-system.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-window.dylib $(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-network.dylib
 



include ProjectConfig.mk

OUT_NAME := $(GAME_TITLE)-v$(GAME_VERSION).$(GAME_SUBVERSION)

.PHONY: all clean rebuild distribution Linux Linux_distribution Darwin  Darwin_distribution

PLATFORM := $(shell uname -s)


all: 
	$(info [INFO]: compiling $(GAME_TITLE) project)
	@$(MAKE) $(PLATFORM)

rebuild: 
	@(cd ../../engine/; make -j$(shell nproc))
	$(info [INFO]: compiling $(GAME_TITLE) project)
	@$(MAKE) $(PLATFORM)

distribution: 
	$(info [INFO]: setting up package structure)
	@rm -fr out/$(PLATFORM)/$(GAME_TITLE)
	@mkdir -p out/$(PLATFORM)
	@mkdir out/$(PLATFORM)/$(GAME_TITLE)
	$(info [INFO]: copying libs and game resources)
	@cp -r $(GAME_RESOURCES_FOLDER) out/$(PLATFORM)/$(GAME_TITLE)/


	$(info [INFO]: compiling $(GAME_TITLE) project)
	@$(MAKE) $(PLATFORM)_distribution


clean:
	$(info [INFO]: cleaning out/)
	@rm -fr out/*

$(ENGINE_PATH)/libengine.dylib:
	$(info [INFO]: engine was not compiled)
	$(info [INFO]: compiling engine...)
	(cd ../../engine/; make -j$(shell nproc))

Darwin: $(ENGINE_PATH)/libengine.dylib
	@$(CC_DARWIN) $(INCLUDE) $(GAME_SOURCES) $(CFLAGS_DARWIN) $(LINKER_FLAGS_DARWIN_BUILD) -o $(GAME_TITLE)
	@install_name_tool -change @rpath/libsfml-graphics.2.5.dylib @executable_path/$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-graphics.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-window.2.5.dylib @executable_path/$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-window.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-system.2.5.dylib @executable_path/$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-system.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change libengine.dylib @executable_path/$(ENGINE_PATH)/libengine.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-network.2.5.dylib @executable_path/$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-network.2.5.1.dylib $(GAME_TITLE)


Darwin_distribution: $(ENGINE_PATH)/libengine.dylib
	@cp -r $(ENGINE_PATH)/thirdparty/lib/$(PLATFORM)/ out/$(PLATFORM)/$(GAME_TITLE)/libs
	@cp $(ENGINE_PATH)/libengine.dylib out/$(PLATFORM)/$(GAME_TITLE)/libs/libengine.dylib
	@$(CC_DARWIN) $(INCLUDE) $(GAME_SOURCES) $(CFLAGS_DARWIN) $(LINKER_FLAGS_DARWIN_BUILD) -o $(GAME_TITLE)
	@install_name_tool -change @rpath/libsfml-graphics.2.5.dylib @executable_path/libs/libsfml-graphics.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-window.2.5.dylib @executable_path/libs/libsfml-window.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-system.2.5.dylib @executable_path/libs/libsfml-system.2.5.1.dylib $(GAME_TITLE) && install_name_tool -change libengine.dylib @executable_path/libs/libengine.dylib $(GAME_TITLE) && install_name_tool -change @rpath/libsfml-network.2.5.dylib @executable_path/$(ENGINE_PATH)/thirdparty/lib/Darwin/libsfml-network.2.5.1.dylib $(GAME_TITLE)

	@mv $(GAME_TITLE) out/$(PLATFORM)/$(GAME_TITLE)/$(GAME_TITLE)

$(ENGINE_PATH)/libengine.so:
	$(info [INFO]: engine was not compiled)
	$(info [INFO]: compiling engine...)
	@(cd ../../engine/; make -j$(shell nproc))

Linux: $(ENGINE_PATH)/libengine.so
	@$(CC_LINUX) $(INCLUDE) $(GAME_SOURCES) $(CFLAGS_LINUX) $(LINKER_FLAGS_LINUX_BUILD) -o $(OUT_NAME).out


Linux_distribution: $(ENGINE_PATH)/libengine.so
	@cp -r $(ENGINE_PATH)/thirdparty/lib/$(PLATFORM)/ out/$(PLATFORM)/$(GAME_TITLE)/
	@mv out/$(PLATFORM)/$(GAME_TITLE)/$(PLATFORM) out/$(PLATFORM)/$(GAME_TITLE)/libs
	@cp $(ENGINE_PATH)/libengine.so out/$(PLATFORM)/$(GAME_TITLE)/libs/libengine.so
	(cd out/$(PLATFORM)/$(GAME_TITLE); $(CC_LINUX) -I../../../sources/ -I../../../$(ENGINE_PATH)/thirdparty/include -I../../../$(ENGINE_PATH)/sources $(subst ./,../../../,$(GAME_SOURCES)) $(CFLAGS_LINUX) $(LINKER_FLAGS_LINUX_DISTRIBUTION) -o $(OUT_NAME))
	

	
