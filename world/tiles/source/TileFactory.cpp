#include <boost/static_assert.hpp>
#include <boost/make_shared.hpp>
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
  BOOST_STATIC_ASSERT(TILE_TYPE_LAST == 41);

  TilePtr barracks = boost::make_shared<BarracksTile>();
  TilePtr barrow   = boost::make_shared<BarrowTile>();
  TilePtr beach    = boost::make_shared<BeachTile>();
  TilePtr bush     = boost::make_shared<BushTile>();
  TilePtr cairn    = boost::make_shared<CairnTile>();
  TilePtr castle   = boost::make_shared<CastleTile>();
  TilePtr cavern   = boost::make_shared<CavernTile>();
  TilePtr church   = boost::make_shared<ChurchTile>();
  TilePtr dais     = boost::make_shared<DaisTile>();
  TilePtr desert   = boost::make_shared<DesertTile>();
  TilePtr downst   = boost::make_shared<DownStaircaseTile>();
  TilePtr dcomp    = boost::make_shared<DungeonComplexTile>();
  TilePtr dungeon  = boost::make_shared<DungeonTile>();
  TilePtr field    = boost::make_shared<FieldTile>();
  TilePtr forest   = boost::make_shared<ForestTile>();
  TilePtr grave    = boost::make_shared<GraveTile>();
  TilePtr grvyard  = boost::make_shared<GraveyardTile>();
  TilePtr hills    = boost::make_shared<HillsTile>();
  TilePtr keep     = boost::make_shared<KeepTile>();
  TilePtr library  = boost::make_shared<LibraryTile>();
  TilePtr marsh    = boost::make_shared<MarshTile>();
  TilePtr mtns     = boost::make_shared<MountainsTile>();
  TilePtr pier     = boost::make_shared<PierTile>();
  TilePtr reeds    = boost::make_shared<ReedsTile>();
  TilePtr river    = boost::make_shared<RiverTile>();
  TilePtr road     = boost::make_shared<RoadTile>();
  TilePtr rock     = boost::make_shared<RockTile>();
  TilePtr scrub    = boost::make_shared<ScrubTile>();
  TilePtr sea      = boost::make_shared<SeaTile>();
  TilePtr shoals   = boost::make_shared<ShoalsTile>();
  TilePtr sodeath  = boost::make_shared<SiteOfDeathTile>();
  TilePtr springs  = boost::make_shared<SpringsTile>();
  TilePtr temple   = boost::make_shared<TempleTile>();
  TilePtr tree     = boost::make_shared<TreeTile>();
  TilePtr upst     = boost::make_shared<UpStaircaseTile>();
  TilePtr village  = boost::make_shared<VillageTile>();
  TilePtr weeds    = boost::make_shared<WeedsTile>();
  TilePtr wheat    = boost::make_shared<WheatTile>();
  TilePtr wild_orchard = boost::make_shared<WildOrchardTile>();
  TilePtr fruit_tree = boost::make_shared<FruitTreeTile>();
  TilePtr evergreen = boost::make_shared<EvergreenTreeTile>();

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
}
