include ../../../makefile.common

INCLUDE=-I../include -I../../include -I../../../engine/include -I../tile/include -I../../../include -I../../../../gtest-1.6.0/include

all: tiles

tiles: Tile.o FieldTile.o ScrubTile.o WheatTile.o CairnTile.o TreeTile.o DesertTile.o RoadTile.o RiverTile.o SeaTile.o ShoalsTile.o DungeonTile.o RockTile.o GraveTile.o MarshTile.o ReedsTile.o HillsTile.o MountainsTile.o BeachTile.o BushTile.o WeedsTile.o SpringsTile.o ForestTile.o StaircaseTile.o UpStaircaseTile.o DownStaircaseTile.o

Tile.o: Tile.cpp ../include/Tile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) Tile.cpp

FieldTile.o: FieldTile.cpp ../include/FieldTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) FieldTile.cpp

ScrubTile.o: ScrubTile.cpp ../include/ScrubTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ScrubTile.cpp

WheatTile.o: WheatTile.cpp ../include/WheatTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) WheatTile.cpp

CairnTile.o: CairnTile.cpp ../include/CairnTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) CairnTile.cpp

TreeTile.o: TreeTile.cpp ../include/TreeTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) TreeTile.cpp

DesertTile.o: DesertTile.cpp ../include/DesertTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DesertTile.cpp

RoadTile.o: RoadTile.cpp ../include/RoadTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RoadTile.cpp

RiverTile.o: RiverTile.cpp ../include/RiverTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RiverTile.cpp

SeaTile.o: SeaTile.cpp ../include/SeaTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SeaTile.cpp

ShoalsTile.o: ShoalsTile.cpp ../include/ShoalsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ShoalsTile.cpp

DungeonTile.o: DungeonTile.cpp ../include/DungeonTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DungeonTile.cpp

RockTile.o: RockTile.cpp ../include/RockTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) RockTile.cpp

GraveTile.o: GraveTile.cpp ../include/GraveTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) GraveTile.cpp

MarshTile.o: MarshTile.cpp ../include/MarshTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MarshTile.cpp

ReedsTile.o: ReedsTile.cpp ../include/ReedsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ReedsTile.cpp

HillsTile.o: HillsTile.cpp ../include/HillsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) HillsTile.cpp

MountainsTile.o: MountainsTile.cpp ../include/MountainsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) MountainsTile.cpp

BeachTile.o: BeachTile.cpp ../include/BeachTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) BeachTile.cpp

BushTile.o: BushTile.cpp ../include/BushTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) BushTile.cpp

WeedsTile.o: WeedsTile.cpp ../include/WeedsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) WeedsTile.cpp

SpringsTile.o: SpringsTile.cpp ../include/SpringsTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) SpringsTile.cpp

ForestTile.o: ForestTile.cpp ../include/ForestTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) ForestTile.cpp

StaircaseTile.o: StaircaseTile.cpp ../include/StaircaseTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) StaircaseTile.cpp

UpStaircaseTile.o: UpStaircaseTile.cpp ../include/StaircaseTile.hpp ../include/UpStaircaseTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) UpStaircaseTile.cpp

DownStaircaseTile.o: DownStaircaseTile.cpp ../include/StaircaseTile.hpp ../include/DownStaircaseTile.hpp
	$(CPP) -c $(CPP_FLAGS) $(INCLUDE) DownStaircaseTile.cpp

clean:
	rm -rf *.o
