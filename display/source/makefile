include ../../makefile.common

INCLUDE=-I../include -I../../engine/include -I../../engine/menus/include -I../../world/include -I../../world/tiles/include -I../../include

display: DisplayMap.o DisplayTile.o NCursesDisplay.o NCursesPromptProcessor.o NCursesMenuWrapper.o NCursesUtils.o

DisplayMap.o: DisplayMap.cpp ../include/DisplayMap.hpp ../include/DisplayTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DisplayMap.cpp

DisplayTile.o: DisplayTile.cpp ../include/DisplayTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DisplayTile.cpp

NCursesDisplay.o: NCursesDisplay.cpp ../include/NCursesDisplay.hpp ../include/Display.hpp 
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesDisplay.cpp

NCursesPromptProcessor.o: NCursesPromptProcessor.cpp ../include/NCursesPromptProcessor.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesPromptProcessor.cpp

NCursesMenuWrapper.o: NCursesMenuWrapper.cpp ../include/NCursesMenuWrapper.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesMenuWrapper.cpp

NCursesUtils.o: NCursesUtils.cpp ../include/NCursesUtils.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesUtils.cpp

clean:
	rm -f *.o
