include ../../makefile.common

INCLUDE=-I../include -I../../engine/include -I../../engine/menus/include -I../../world/include -I../../world/tiles/include -I../../include

display: NCursesDisplay.o NCursesPromptProcessor.o

NCursesDisplay.o: NCursesDisplay.cpp ../include/NCursesDisplay.hpp ../include/Display.hpp 
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesDisplay.cpp

NCursesPromptProcessor.o: NCursesPromptProcessor.cpp ../include/NCursesPromptProcessor.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NCursesPromptProcessor.cpp

clean:
	rm -f *.o
