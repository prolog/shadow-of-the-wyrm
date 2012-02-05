#include <boost/make_shared.hpp>
#include "CavernGenerator.hpp"
#include "FieldGenerator.hpp"
#include "ForestGenerator.hpp"
#include "MarshGenerator.hpp"
#include "MountainsGenerator.hpp"
#include "SeaGenerator.hpp"
#include "TerrainGeneratorFactory.hpp"

using boost::make_shared;

TerrainGeneratorFactory::TerrainGeneratorFactory()
{
}

TerrainGeneratorFactory::~TerrainGeneratorFactory()
{
}

// Create a generator based on the tile passed in.  The world map uses a limited
// subset of the overall tiles (field, forest, sea, desert, etc., but not grave, 
// reeds, etc).  Any unsupported tile for terrain generation will get a null GeneratorPtr back.
GeneratorPtr TerrainGeneratorFactory::create_generator(const TileType terrain_type)
{
  GeneratorPtr generator;
  
  switch(terrain_type)
  {
    case TILE_TYPE_FIELD:
      generator = make_shared<FieldGenerator>();
      break;
    case TILE_TYPE_SEA:
      generator = make_shared<SeaGenerator>();
      break;
    case TILE_TYPE_MARSH:
      generator = make_shared<MarshGenerator>();
      break;
    case TILE_TYPE_MOUNTAINS:
      generator = make_shared<MountainsGenerator>();
      break;
    case TILE_TYPE_FOREST:
      generator = make_shared<ForestGenerator>();
      break;
    case TILE_TYPE_CAVERN:
      generator = make_shared<CavernGenerator>();
      break;
    case TILE_TYPE_UNDEFINED:
    case TILE_TYPE_SCRUB:
    case TILE_TYPE_WHEAT:
    case TILE_TYPE_CAIRN:
    case TILE_TYPE_TREE:
    case TILE_TYPE_DESERT:
    case TILE_TYPE_ROAD:
    case TILE_TYPE_RIVER:
    case TILE_TYPE_SHOALS:
    case TILE_TYPE_DUNGEON:
    case TILE_TYPE_ROCK:
    case TILE_TYPE_GRAVE:
    case TILE_TYPE_REEDS:
    case TILE_TYPE_HILLS:
    case TILE_TYPE_BEACH:
    case TILE_TYPE_BUSH:
    case TILE_TYPE_WEEDS:
    case TILE_TYPE_SPRINGS:
    case TILE_TYPE_UP_STAIRCASE:
    case TILE_TYPE_DOWN_STAIRCASE:
    case TILE_TYPE_VILLAGE:
    default:
      // Right now, everything generates a field.  Change this once testing is complete.
      generator = make_shared<FieldGenerator>();
      break;
  }
  
  return generator;
}
