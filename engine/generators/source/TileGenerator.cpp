#include "TileGenerator.hpp"
#include "tiles.hpp"
#include "AllTiles.hpp"

TilePtr TileGenerator::generate(const TileType& tile_type)
{
  TilePtr result_tile;

  switch(tile_type)
  {
    case TILE_TYPE_FIELD:
      result_tile = TilePtr(new FieldTile());
      break;
    case TILE_TYPE_SCRUB:
      result_tile = TilePtr(new ScrubTile());
      break;
    case TILE_TYPE_WHEAT:
      result_tile = TilePtr(new WheatTile());
      break;
    case TILE_TYPE_CAIRN:
      result_tile = TilePtr(new CairnTile());
      break;
    case TILE_TYPE_TREE:
      result_tile = TilePtr(new TreeTile());
      break;
    case TILE_TYPE_DESERT:
      result_tile = TilePtr(new DesertTile());
      break;
    case TILE_TYPE_ROAD:
      result_tile = TilePtr(new RoadTile());
      break;
    case TILE_TYPE_RIVER:
      result_tile = TilePtr(new RiverTile());
      break;
    case TILE_TYPE_SEA:
      result_tile = TilePtr(new SeaTile());
      break;
    case TILE_TYPE_SHOALS:
      result_tile = TilePtr(new ShoalsTile());
      break;
    case TILE_TYPE_DUNGEON:
      result_tile = TilePtr(new DungeonTile());
      break;
    case TILE_TYPE_ROCK:
      result_tile = TilePtr(new RockTile());
      break;
    case TILE_TYPE_GRAVE:
      result_tile = TilePtr(new GraveTile());
      break;
    case TILE_TYPE_MARSH:
      result_tile = TilePtr(new MarshTile());
      break;
    case TILE_TYPE_REEDS:
      result_tile = TilePtr(new ReedsTile());
      break;
    case TILE_TYPE_HILLS:
      result_tile = TilePtr(new HillsTile());
      break;
    case TILE_TYPE_MOUNTAINS:
      result_tile = TilePtr(new MountainsTile());
      break;
    case TILE_TYPE_BEACH:
      result_tile = TilePtr(new BeachTile());
      break;
    case TILE_TYPE_BUSH:
      result_tile = TilePtr(new BushTile());
      break;
    case TILE_TYPE_WEEDS:
      result_tile = TilePtr(new WeedsTile());
      break;
    case TILE_TYPE_SPRINGS:
      result_tile = TilePtr(new SpringsTile());
      break;
    case TILE_TYPE_FOREST:
      result_tile = TilePtr(new ForestTile());
      break;
    case TILE_TYPE_UP_STAIRCASE:
      result_tile = TilePtr(new UpStaircaseTile());
      break;
    case TILE_TYPE_DOWN_STAIRCASE:
      result_tile = TilePtr(new DownStaircaseTile());
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
