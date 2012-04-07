#include <boost/make_shared.hpp>
#include "CavernGenerator.hpp"
#include "DesertGenerator.hpp"
#include "DungeonGenerator.hpp"
#include "FieldGenerator.hpp"
#include "ForestGenerator.hpp"
#include "MarshGenerator.hpp"
#include "MountainsGenerator.hpp"
#include "ScrubGenerator.hpp"
#include "SeaGenerator.hpp"
#include "SettlementGenerator.hpp"
#include "TerrainGeneratorFactory.hpp"

using std::string;
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
GeneratorPtr TerrainGeneratorFactory::create_generator(const string& map_exit_id, const TileType terrain_type, const TileType terrain_subtype)
{
  GeneratorPtr generator;
  
  switch(terrain_type)
  {
    case TILE_TYPE_FIELD:
      generator = make_shared<FieldGenerator>(map_exit_id);
      break;
    case TILE_TYPE_SEA:
      generator = make_shared<SeaGenerator>(map_exit_id);
      break;
    case TILE_TYPE_MARSH:
      generator = make_shared<MarshGenerator>(map_exit_id);
      break;
    case TILE_TYPE_MOUNTAINS:
      generator = make_shared<MountainsGenerator>(map_exit_id);
      break;
    case TILE_TYPE_FOREST:
      generator = make_shared<ForestGenerator>(map_exit_id);
      break;
    case TILE_TYPE_CAVERN:
      generator = make_shared<CavernGenerator>(map_exit_id);
      break;
    case TILE_TYPE_DESERT:
      generator = make_shared<DesertGenerator>(map_exit_id);
      break;
    case TILE_TYPE_SCRUB:
      generator = make_shared<ScrubGenerator>(map_exit_id);
      break;
    case TILE_TYPE_VILLAGE:
    {
      GeneratorPtr base_generator = create_generator(map_exit_id, terrain_subtype);
      MapPtr base_map = base_generator->generate();
      generator = make_shared<SettlementGenerator>(base_map);
    }
      break;
    case TILE_TYPE_DUNGEON_COMPLEX:
      generator = make_shared<DungeonGenerator>(map_exit_id);
      break;
    case TILE_TYPE_UNDEFINED:
    case TILE_TYPE_WHEAT:
    case TILE_TYPE_CAIRN:
    case TILE_TYPE_TREE:
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
    case TILE_TYPE_BARRACKS:
    case TILE_TYPE_CASTLE:
    case TILE_TYPE_CHURCH:
    case TILE_TYPE_GRAVEYARD:
    case TILE_TYPE_KEEP:
    case TILE_TYPE_LIBRARY:
    case TILE_TYPE_SITE_OF_DEATH:
    case TILE_TYPE_TEMPLE:
    case TILE_TYPE_DAIS:
    default:
      // Right now, everything generates a field.  Change this once testing is complete.
      generator = make_shared<FieldGenerator>(map_exit_id);
      break;
  }
  
  return generator;
}
