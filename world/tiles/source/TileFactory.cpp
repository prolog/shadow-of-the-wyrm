#include <boost/static_assert.hpp>
#include "AllTiles.hpp"
#include "TileFactory.hpp"

using namespace std;

TileSerializationMap TileFactory::tiles_map;

TileFactory::TileFactory()
{
}

TileFactory::~TileFactory()
{
}

TilePtr TileFactory::create_tile(const ClassIdentifier cl_id)
{
  TilePtr tile;

  if (tiles_map.empty())
  {
    initialize_tile_map();
  }

  TileSerializationMap::iterator t_it = tiles_map.find(cl_id);

  if (t_it != tiles_map.end())
  {
    tile = TilePtr(t_it->second->clone());
  }

  return tile;
}

void TileFactory::initialize_tile_map()
{
  BOOST_STATIC_ASSERT(TILE_TYPE_LAST == 44);

  TilePtr barracks = std::make_shared<BarracksTile>();
  TilePtr barrow   = std::make_shared<BarrowTile>();
  TilePtr beach    = std::make_shared<BeachTile>();
  TilePtr bush     = std::make_shared<BushTile>();
  TilePtr cairn    = std::make_shared<CairnTile>();
  TilePtr castle   = std::make_shared<CastleTile>();
  TilePtr cavern   = std::make_shared<CavernTile>();
  TilePtr church   = std::make_shared<ChurchTile>();
  TilePtr dais     = std::make_shared<DaisTile>();
  TilePtr desert   = std::make_shared<DesertTile>();
  TilePtr downst   = std::make_shared<DownStaircaseTile>();
  TilePtr dcomp    = std::make_shared<DungeonComplexTile>();
  TilePtr dungeon  = std::make_shared<DungeonTile>();
  TilePtr field    = std::make_shared<FieldTile>();
  TilePtr forest   = std::make_shared<ForestTile>();
  TilePtr grave    = std::make_shared<GraveTile>();
  TilePtr grvyard  = std::make_shared<GraveyardTile>();
  TilePtr hills    = std::make_shared<HillsTile>();
  TilePtr keep     = std::make_shared<KeepTile>();
  TilePtr library  = std::make_shared<LibraryTile>();
  TilePtr marsh    = std::make_shared<MarshTile>();
  TilePtr mtns     = std::make_shared<MountainsTile>();
  TilePtr pier     = std::make_shared<PierTile>();
  TilePtr reeds    = std::make_shared<ReedsTile>();
  TilePtr river    = std::make_shared<RiverTile>();
  TilePtr road     = std::make_shared<RoadTile>();
  TilePtr rock     = std::make_shared<RockTile>();
  TilePtr scrub    = std::make_shared<ScrubTile>();
  TilePtr sea      = std::make_shared<SeaTile>();
  TilePtr shoals   = std::make_shared<ShoalsTile>();
  TilePtr sodeath  = std::make_shared<SiteOfDeathTile>();
  TilePtr springs  = std::make_shared<SpringsTile>();
  TilePtr temple   = std::make_shared<TempleTile>();
  TilePtr tree     = std::make_shared<TreeTile>();
  TilePtr upst     = std::make_shared<UpStaircaseTile>();
  TilePtr village  = std::make_shared<VillageTile>();
  TilePtr weeds    = std::make_shared<WeedsTile>();
  TilePtr wheat    = std::make_shared<WheatTile>();
  TilePtr wild_orchard = std::make_shared<WildOrchardTile>();
  TilePtr fruit_tree = std::make_shared<FruitTreeTile>();
  TilePtr evergreen = std::make_shared<EvergreenTreeTile>();
  TilePtr rocky_earth = std::make_shared<RockyEarthTile>();
  TilePtr mine     = std::make_shared<MineTile>();
  TilePtr well     = std::make_shared<WellTile>();

  tiles_map.insert(make_pair(CLASS_ID_BARRACKS_TILE, barracks));
  tiles_map.insert(make_pair(CLASS_ID_BARROW_TILE, barrow));
  tiles_map.insert(make_pair(CLASS_ID_BEACH_TILE, beach));
  tiles_map.insert(make_pair(CLASS_ID_BUSH_TILE, bush));
  tiles_map.insert(make_pair(CLASS_ID_CAIRN_TILE, cairn));
  tiles_map.insert(make_pair(CLASS_ID_CASTLE_TILE, castle));
  tiles_map.insert(make_pair(CLASS_ID_CAVERN_TILE, cavern));
  tiles_map.insert(make_pair(CLASS_ID_CHURCH_TILE, church));
  tiles_map.insert(make_pair(CLASS_ID_DAIS_TILE, dais));
  tiles_map.insert(make_pair(CLASS_ID_DESERT_TILE, desert));
  tiles_map.insert(make_pair(CLASS_ID_DOWN_STAIRCASE_TILE, downst));
  tiles_map.insert(make_pair(CLASS_ID_DUNGEON_COMPLEX_TILE, dcomp));
  tiles_map.insert(make_pair(CLASS_ID_DUNGEON_TILE, dungeon));
  tiles_map.insert(make_pair(CLASS_ID_FIELD_TILE, field));
  tiles_map.insert(make_pair(CLASS_ID_FOREST_TILE, forest));
  tiles_map.insert(make_pair(CLASS_ID_GRAVE_TILE, grave));
  tiles_map.insert(make_pair(CLASS_ID_GRAVEYARD_TILE, grvyard));
  tiles_map.insert(make_pair(CLASS_ID_HILLS_TILE, hills));
  tiles_map.insert(make_pair(CLASS_ID_KEEP_TILE, keep));
  tiles_map.insert(make_pair(CLASS_ID_LIBRARY_TILE, library));
  tiles_map.insert(make_pair(CLASS_ID_MARSH_TILE, marsh));
  tiles_map.insert(make_pair(CLASS_ID_MOUNTAINS_TILE, mtns));
  tiles_map.insert(make_pair(CLASS_ID_PIER_TILE, pier));
  tiles_map.insert(make_pair(CLASS_ID_REEDS_TILE, reeds));
  tiles_map.insert(make_pair(CLASS_ID_RIVER_TILE, river));
  tiles_map.insert(make_pair(CLASS_ID_ROAD_TILE, road));
  tiles_map.insert(make_pair(CLASS_ID_ROCK_TILE, rock));
  tiles_map.insert(make_pair(CLASS_ID_SCRUB_TILE, scrub));
  tiles_map.insert(make_pair(CLASS_ID_SEA_TILE, sea));
  tiles_map.insert(make_pair(CLASS_ID_SHOALS_TILE, shoals));
  tiles_map.insert(make_pair(CLASS_ID_SITE_OF_DEATH_TILE, sodeath));
  tiles_map.insert(make_pair(CLASS_ID_SPRINGS_TILE, springs));
  tiles_map.insert(make_pair(CLASS_ID_TEMPLE_TILE, temple));
  tiles_map.insert(make_pair(CLASS_ID_TREE_TILE, tree));
  tiles_map.insert(make_pair(CLASS_ID_UP_STAIRCASE_TILE, upst));
  tiles_map.insert(make_pair(CLASS_ID_VILLAGE_TILE, village));
  tiles_map.insert(make_pair(CLASS_ID_WEEDS_TILE, weeds));
  tiles_map.insert(make_pair(CLASS_ID_WHEAT_TILE, wheat));
  tiles_map.insert(make_pair(CLASS_ID_WILD_ORCHARD_TILE, wild_orchard));
  tiles_map.insert(make_pair(CLASS_ID_FRUIT_TREE_TILE, fruit_tree));
  tiles_map.insert(make_pair(CLASS_ID_EVERGREEN_TREE_TILE, evergreen));
  tiles_map.insert(make_pair(CLASS_ID_ROCKY_EARTH_TILE, rocky_earth));
  tiles_map.insert(make_pair(CLASS_ID_MINE_TILE, mine));
  tiles_map.insert(make_pair(CLASS_ID_WELL_TILE, well));
}
