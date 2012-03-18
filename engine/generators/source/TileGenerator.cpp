#include <boost/make_shared.hpp>
#include "Log.hpp"
#include "TileGenerator.hpp"
#include "tiles.hpp"
#include "AllTiles.hpp"

using boost::make_shared;

TilePtr TileGenerator::generate(const TileType& tile_type, const TileType& subtile_type)
{
  TilePtr result_tile;

  switch(tile_type)
  {
    case TILE_TYPE_UNDEFINED:
      Log::instance()->log("Attempting to generate an undefined tile type");
      break;
    case TILE_TYPE_FIELD:
      result_tile = make_shared<FieldTile>();
      break;
    case TILE_TYPE_SCRUB:
      result_tile = make_shared<ScrubTile>();
      break;
    case TILE_TYPE_WHEAT:
      result_tile = make_shared<WheatTile>();
      break;
    case TILE_TYPE_CAIRN:
      result_tile = make_shared<CairnTile>();
      break;
    case TILE_TYPE_TREE:
      result_tile = make_shared<TreeTile>();
      break;
    case TILE_TYPE_DESERT:
      result_tile = make_shared<DesertTile>();
      break;
    case TILE_TYPE_ROAD:
      result_tile = make_shared<RoadTile>();
      break;
    case TILE_TYPE_RIVER:
      result_tile = make_shared<RiverTile>();
      break;
    case TILE_TYPE_SEA:
      result_tile = make_shared<SeaTile>();
      break;
    case TILE_TYPE_SHOALS:
      result_tile = make_shared<ShoalsTile>();
      break;
    case TILE_TYPE_DUNGEON:
      result_tile = make_shared<DungeonTile>();
      break;
    case TILE_TYPE_ROCK:
      result_tile = make_shared<RockTile>();
      break;
    case TILE_TYPE_GRAVE:
      result_tile = make_shared<GraveTile>();
      break;
    case TILE_TYPE_MARSH:
      result_tile = make_shared<MarshTile>();
      break;
    case TILE_TYPE_REEDS:
      result_tile = make_shared<ReedsTile>();
      break;
    case TILE_TYPE_HILLS:
      result_tile = make_shared<HillsTile>();
      break;
    case TILE_TYPE_MOUNTAINS:
      result_tile = make_shared<MountainsTile>();
      break;
    case TILE_TYPE_BEACH:
      result_tile = make_shared<BeachTile>();
      break;
    case TILE_TYPE_BUSH:
      result_tile = make_shared<BushTile>();
      break;
    case TILE_TYPE_WEEDS:
      result_tile = make_shared<WeedsTile>();
      break;
    case TILE_TYPE_SPRINGS:
      result_tile = make_shared<SpringsTile>();
      break;
    case TILE_TYPE_FOREST:
      result_tile = make_shared<ForestTile>();
      break;
    case TILE_TYPE_UP_STAIRCASE:
      result_tile = make_shared<UpStaircaseTile>();
      break;
    case TILE_TYPE_DOWN_STAIRCASE:
      result_tile = make_shared<DownStaircaseTile>();
      break;
    case TILE_TYPE_CAVERN:
      result_tile = make_shared<CavernTile>();
      break;
    case TILE_TYPE_VILLAGE:
      result_tile = make_shared<VillageTile>(subtile_type);
      break;
    case TILE_TYPE_DUNGEON_COMPLEX:
      result_tile = make_shared<DungeonComplexTile>();
      break;
    case TILE_TYPE_BARRACKS:
      result_tile = make_shared<BarracksTile>();
      break;
    case TILE_TYPE_CASTLE:
      result_tile = make_shared<CastleTile>();
      break;
    case TILE_TYPE_CHURCH:
      result_tile = make_shared<ChurchTile>();
      break;
    case TILE_TYPE_GRAVEYARD:
      result_tile = make_shared<GraveyardTile>();
      break;
    case TILE_TYPE_KEEP:
      result_tile = make_shared<KeepTile>();
      break;
    case TILE_TYPE_LIBRARY:
      result_tile = make_shared<LibraryTile>();
      break;
    case TILE_TYPE_SITE_OF_DEATH:
      result_tile = make_shared<SiteOfDeathTile>();
      break;
    case TILE_TYPE_TEMPLE:
      result_tile = make_shared<TempleTile>();
      break;
    default:
      break;
  }

  return result_tile;
}

StaircaseTilePtr TileGenerator::generate_staircase(const StaircaseType& staircase_type)
{
  StaircaseTilePtr result_tile;

  switch(staircase_type)
  {
    case STAIRCASE_UP:
      result_tile = UpStaircaseTilePtr(new UpStaircaseTile());
      break;
    case STAIRCASE_DOWN:
      result_tile = DownStaircaseTilePtr(new DownStaircaseTile());
      break;
    default:
      break;
  }

  return result_tile;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileGenerator_test.cpp"
#endif
