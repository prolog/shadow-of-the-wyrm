#include <boost/make_shared.hpp>
#include "CavernGenerator.hpp"
#include "DesertGenerator.hpp"
#include "DungeonGenerator.hpp"
#include "FieldGenerator.hpp"
#include "ForestGenerator.hpp"
#include "Game.hpp"
#include "GraveyardGeneratorFactory.hpp"
#include "HillsGenerator.hpp"
#include "MarshGenerator.hpp"
#include "MountainsGenerator.hpp"
#include "RaceManager.hpp"
#include "ScrubGenerator.hpp"
#include "SeaGenerator.hpp"
#include "SettlementGeneratorFactory.hpp"
#include "TerrainGeneratorFactory.hpp"
#include "WorshipSiteGenerator.hpp"
#include "WorshipSiteTile.hpp"
#include "VillageTile.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

TerrainGeneratorFactory::TerrainGeneratorFactory()
{
}

TerrainGeneratorFactory::~TerrainGeneratorFactory()
{
}

// Create a generator based on the tile passed in.  The world map uses a limited
// subset of the overall tiles (field, forest, sea, desert, etc., but not grave, 
// reeds, etc).  Any unsupported tile for terrain generation will get a null GeneratorPtr back.
GeneratorPtr TerrainGeneratorFactory::create_generator(TilePtr tile, const string& map_exit_id, const TileType terrain_type, const TileType terrain_subtype)
{
  GeneratorPtr generator;
  
  switch(terrain_type)
  {
    case TILE_TYPE_FIELD:
      generator = boost::make_shared<FieldGenerator>(map_exit_id);
      break;
    case TILE_TYPE_SEA:
      generator = boost::make_shared<SeaGenerator>(map_exit_id);
      break;
    case TILE_TYPE_MARSH:
      generator = boost::make_shared<MarshGenerator>(map_exit_id);
      break;
    case TILE_TYPE_MOUNTAINS:
      generator = boost::make_shared<MountainsGenerator>(map_exit_id);
      break;
    case TILE_TYPE_HILLS:
      generator = boost::make_shared<HillsGenerator>(map_exit_id);
      break;
    case TILE_TYPE_FOREST:
      generator = boost::make_shared<ForestGenerator>(map_exit_id);
      break;
    case TILE_TYPE_CAVERN:
      generator = boost::make_shared<CavernGenerator>(map_exit_id);
      break;
    case TILE_TYPE_DESERT:
      generator = boost::make_shared<DesertGenerator>(map_exit_id);
      break;
    case TILE_TYPE_SCRUB:
      generator = boost::make_shared<ScrubGenerator>(map_exit_id);
      break;
    case TILE_TYPE_VILLAGE:
    {      
      GeneratorPtr base_generator = create_generator(tile, map_exit_id, terrain_subtype);
      MapPtr base_map = base_generator->generate();
      
      SettlementType settlement_type = SETTLEMENT_TYPE_ORDERLY_VILLAGE;
      
      VillageTilePtr village_tile = dynamic_pointer_cast<VillageTile>(tile);
      
      if (village_tile)
      {
        RaceManager rm;
        RacePtr race = rm.get_race(village_tile->get_village_race_id());
        
        if (race)
        {
          settlement_type = race->get_settlement_type();          
        }
      }

      generator = SettlementGeneratorFactory::create_settlement_generator(settlement_type, base_map);
    }
      break;
    case TILE_TYPE_GRAVEYARD:
      generator = GraveyardGeneratorFactory::create_scattered_graveyard_generator(map_exit_id, true);
      break;
    case TILE_TYPE_DUNGEON_COMPLEX:
      generator = boost::make_shared<DungeonGenerator>(map_exit_id);
      break;
    // All three worship sites use the same process:
    case TILE_TYPE_CHURCH:
    case TILE_TYPE_SITE_OF_DEATH:
    case TILE_TYPE_TEMPLE:
    {
      WorshipSiteTilePtr worship_site_tile = dynamic_pointer_cast<WorshipSiteTile>(tile);
      
      if (worship_site_tile)
      {
        GeneratorPtr base_generator = create_generator(tile, map_exit_id, terrain_subtype);
        MapPtr base_map = base_generator->generate();
        generator = WorshipSiteGenerator::generate_worship_site(worship_site_tile->get_worship_site_type(), worship_site_tile->get_deity_id(), base_map);
      }

      break;      
    }
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
    case TILE_TYPE_BEACH:
    case TILE_TYPE_BUSH:
    case TILE_TYPE_WEEDS:
    case TILE_TYPE_SPRINGS:
    case TILE_TYPE_UP_STAIRCASE:
    case TILE_TYPE_DOWN_STAIRCASE:
    case TILE_TYPE_BARRACKS:
    case TILE_TYPE_CASTLE:
    case TILE_TYPE_KEEP:
    case TILE_TYPE_LIBRARY:
    case TILE_TYPE_DAIS:
    case TILE_TYPE_PIER:
    default:
      // Right now, everything generates a field.  Change this once testing is complete.
      generator = boost::make_shared<FieldGenerator>(map_exit_id);
      break;
  }

  copy_properties(tile, generator);
  
  return generator;
}

// Copy properties from the tile to the generator's additional properties.
void TerrainGeneratorFactory::copy_properties(TilePtr tile, GeneratorPtr generator)
{
  if (tile && generator)
  {
    map<string, string> tile_properties = tile->get_additional_properties();

    for (map<string, string>::const_iterator p_it = tile_properties.begin(); p_it != tile_properties.end(); p_it++)
    {
      generator->set_additional_property(p_it->first, p_it->second);
    }
  }
}