include ../../makefile.common

INCLUDE=-I../include -I../../engine/include -I../tiles/include -I../../../gtest-1.6.0/include -I../../include

all: world

world: Class.o Creature.o Race.o Map.o Resistances.o Skills.o Statistic.o
	cd ../tiles/source ; make all

Class.o: Class.cpp ../include/Class.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Class.cpp

Creature.o: Creature.cpp ../include/Creature.hpp ../include/CreatureFeatures.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Creature.cpp

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

clean:
	cd ../tiles/source ; make clean
	rm -rf *.o
