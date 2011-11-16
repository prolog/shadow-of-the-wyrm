-include ../../../makefile.common

INCLUDE=-I../include -I../../include -I../../../world/include -I../../../world/tiles/include -I../../../../gtest-1.6.0/include -I../../../include

all: generators

generators: CavernGenerator.o CellularAutomataGenerator.o DungeonGenerator.o FieldGenerator.o ForestGenerator.o KeepRuinsGenerator.o MarshGenerator.o RoadGenerator.o RuinsGenerator.o SettlementGenerator.o SettlementRuinsGenerator.o SpiralDungeonGenerator.o SpringsGenerator.o StreamGenerator.o WorldGenerator.o TileGenerator.o Generator.o

CavernGenerator.o: CavernGenerator.cpp ../include/CavernGenerator.hpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) CavernGenerator.cpp

CellularAutomataGenerator.o: CellularAutomataGenerator.cpp ../include/CellularAutomataGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) CellularAutomataGenerator.cpp

DungeonGenerator.o: DungeonGenerator.cpp ../include/DungeonGenerator.hpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DungeonGenerator.cpp

FieldGenerator.o: FieldGenerator.cpp ../include/FieldGenerator.hpp ../include/Generator.hpp 
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) FieldGenerator.cpp

ForestGenerator.o: ForestGenerator.cpp ../include/ForestGenerator.hpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ForestGenerator.cpp

MarshGenerator.o: MarshGenerator.cpp ../include/MarshGenerator.hpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MarshGenerator.cpp

KeepRuinsGenerator.o: KeepRuinsGenerator.cpp ../include/KeepRuinsGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) KeepRuinsGenerator.cpp

RoadGenerator.o: RoadGenerator.cpp ../include/RoadGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RoadGenerator.cpp

RuinsGenerator.o: RuinsGenerator.cpp ../include/RuinsGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RuinsGenerator.cpp

SettlementGenerator.o: SettlementGenerator.cpp ../include/SettlementGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SettlementGenerator.cpp

SettlementRuinsGenerator.o: SettlementRuinsGenerator.cpp ../include/SettlementRuinsGenerator.hpp ../include/SettlementGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SettlementRuinsGenerator.cpp

SpiralDungeonGenerator.o: SpiralDungeonGenerator.cpp ../include/SpiralDungeonGenerator.hpp ../include/DungeonGenerator.hpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SpiralDungeonGenerator.cpp

SpringsGenerator.o: SpringsGenerator.cpp ../include/SpringsGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SpringsGenerator.cpp

StreamGenerator.o: StreamGenerator.cpp ../include/StreamGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) StreamGenerator.cpp

WorldGenerator.o: WorldGenerator.cpp ../include/WorldGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) WorldGenerator.cpp

TileGenerator.o: TileGenerator.cpp ../include/TileGenerator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) TileGenerator.cpp

Generator.o: Generator.cpp ../include/Generator.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Generator.cpp

clean:
	rm -rf *.o
