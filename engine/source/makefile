-include ../../makefile.common

INCLUDE=-I../include -I../../include -I../XML/include -I../menus/include -I../../../gtest-1.6.0/include -I../../world/include -I../../world/tiles/include -I../../display/include

all: engine

engine: Conversion.o CreatureFactory.o Game.o RNG.o MapUtils.o MessageManager.o Messages.o Message.o SavageLandsEngine.o StringConstants.o StringTable.o Dimensions.o
	cd ../generators/source ; make all
	cd ../menus/source ; make all
	cd ../XML/source ; make all

Conversion.o: Conversion.cpp ../include/Conversion.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Conversion.cpp

CreatureFactory.o: CreatureFactory.cpp ../include/CreatureFactory.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) CreatureFactory.cpp

Game.o: Game.cpp ../include/Game.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Game.cpp

RNG.o: RNG.cpp ../include/RNG.hpp 
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RNG.cpp

MapUtils.o: MapUtils.cpp ../include/MapUtils.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MapUtils.cpp

MessageManager.o: MessageManager.cpp Messages.o ../include/MessageManager.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MessageManager.cpp

Messages.o: Messages.cpp ../include/Messages.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Messages.cpp

Message.o: Message.cpp ../include/Message.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Message.cpp

SavageLandsEngine.o: SavageLandsEngine.cpp ../include/SavageLandsEngine.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SavageLandsEngine.cpp

StringConstants.o: StringConstants.cpp ../include/StringConstants.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) StringConstants.cpp

StringTable.o: StringTable.cpp ../include/StringTable.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) StringTable.cpp

Dimensions.o: Dimensions.cpp ../include/Dimensions.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Dimensions.cpp

clean:
	cd ../generators/source ; make clean
	cd ../menus/source ; make clean
	cd ../XML/source ; make clean
	rm -f *.o
