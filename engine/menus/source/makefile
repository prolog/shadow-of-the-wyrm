-include ../../../makefile.common

INCLUDE=-I../include -I../../../world/include -I../../../world/tiles/include -I../../include -I../../../../gtest-1.6.0/include -I../../../include -I ../../../display/include

all: menus

menus: ClassSelectionScreen.o Menu.o MenuComponent.o NamingScreen.o OptionsComponent.o Prompt.o RaceSelectionScreen.o TextComponent.o WelcomeScreen.o

ClassSelectionScreen.o: ClassSelectionScreen.cpp ../include/ClassSelectionScreen.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ClassSelectionScreen.cpp

Menu.o: Menu.cpp ../include/Menu.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Menu.cpp

MenuComponent.o: MenuComponent.cpp ../include/MenuComponent.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MenuComponent.cpp

NamingScreen.o: NamingScreen.cpp ../include/NamingScreen.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) NamingScreen.cpp

OptionsComponent.o: OptionsComponent.cpp ../include/OptionsComponent.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) OptionsComponent.cpp

Prompt.o: Prompt.cpp ../include/Prompt.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Prompt.cpp

RaceSelectionScreen.o: RaceSelectionScreen.cpp ../include/RaceSelectionScreen.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RaceSelectionScreen.cpp

TextComponent.o: TextComponent.cpp ../include/TextComponent.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) TextComponent.cpp

WelcomeScreen.o: WelcomeScreen.cpp ../include/WelcomeScreen.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) WelcomeScreen.cpp

clean:
	rm -rf *.o
