######################################################################
#                                                                    #
#                       Savage Lands Makefile                        #
#                                                                    #		
######################################################################
include makefile.common

Debug: SavageLands
Release: SavageLands
map: MapTester.o

all: SavageLands

ENGINE_OBJS  := $(patsubst %.cpp,%.o,$(wildcard engine/source/*.cpp))
ENGINE_GENERATORS_OBJS := $(patsubst %.cpp,%.o,$(wildcard engine/generators/source/*.cpp))
ENGINE_XML_OBJS := $(patsubst %.cpp,%.o,$(wildcard engine/XML/source/*.cpp))
ENGINE_MENU_OBJS := $(patsubst %.cpp,%.o,$(wildcard engine/menus/source/*.cpp))
WORLD_OBJS   := $(patsubst %.cpp,%.o,$(wildcard world/source/*.cpp))
WORLD_TILES_OBJS := $(patsubst %.cpp,%.o,$(wildcard world/tiles/source/*.cpp))
DISPLAY_OBJS := $(patsubst %.cpp,%.o,$(wildcard display/source/*.cpp))
BASE_OBJ     := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
BASE_OBJS    := $(filter-out MapTester.o, $(BASE_OBJ))

SavageLands: SavageLands.o global_functions.o
	cd ./world/source ; make world
	cd ./engine/source ; make engine
	cd ./display/source ; make display
	$(CPP) $(CPP_FLAGS) $(BASE_OBJS) $(ENGINE_OBJS) $(ENGINE_GENERATORS_OBJS) $(ENGINE_MENU_OBJS) $(ENGINE_XML_OBJS) $(DISPLAY_OBJS) $(WORLD_OBJS) $(WORLD_TILES_OBJS) $(POST) -o SavageLands -lmenu -lncurses -lxerces-c

SavageLands.o: SavageLands.cpp
	$(CPP) -c $(CPP_FLAGS) SavageLands.cpp
	
global_functions.o: global_functions.cpp
	$(CPP) -c $(CPP_FLAGS) global_functions.cpp

ifeq ($(mode), map)
MapTester.o: MapTester.cpp
	$(CPP) -c $(CPP_FLAGS) MapTester.cpp
	$(CPP) $(CPP_FLAGS) $(ENGINE_OBJS) $(ENGINE_GENERATORS_OBJS) $(ENGINE_XML_OBJS) $(WORLD_OBJS) $(WORLD_TILES_OBJS) MapTester.o -o MapTester -lxerces-c
endif

clean: clean_dumps
	rm -f *.o SavageLands *.html
	cd ./world/source ; make clean
	cd ./engine/source ; make clean
	cd ./display/source ; make clean

clean_dumps:
	rm -rf gvim.exe.stackdump
