include ../../makefile.common

INCLUDE=-I../include -I../../engine/include -I../../engine/menus/include -I../../world/include -I../../world/tiles/include -I../../include

display: NCursesDisplay.o NCursesPromptProcessor.o NCursesMenuWrapper.o NCursesUtils.o

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
