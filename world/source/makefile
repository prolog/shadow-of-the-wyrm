include ../../makefile.common

INCLUDE=-I../include -I../../engine/include -I../tiles/include -I../../../gtest-1.6.0/include -I../../include

all: world_structures

world_structures: Class.o Creature.o Inventory.o Item.o Race.o Map.o Resistances.o Skills.o Statistic.o World.o
	cd ../tiles/source ; make all

Class.o: Class.cpp ../include/Class.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Class.cpp

Creature.o: Creature.cpp ../include/Creature.hpp ../include/CreatureFeatures.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Creature.cpp

Inventory.o: Inventory.cpp ../include/Inventory.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Inventory.cpp

Item.o: Item.cpp ../include/Item.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Item.cpp

Map.o: Map.cpp ../include/Map.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Map.cpp

Race.o: Race.cpp ../include/Race.hpp ../include/Skills.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Race.cpp

Resistances.o: Resistances.cpp ../include/Resistances.hpp ../include/ResistanceTypes.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Resistances.cpp

Skills.o: Skills.cpp ../include/Skills.hpp ../include/SkillTypes.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Skills.cpp

Statistic.o: Statistic.cpp ../include/Statistic.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Statistic.cpp

World.o: World.cpp ../include/World.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) World.cpp

clean-world:
	rm *.o

clean:
	cd ../tiles/source ; make clean
	rm *.o
