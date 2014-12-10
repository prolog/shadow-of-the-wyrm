#include "Game.hpp"
#include "MapTimeObserver.hpp"
#include "TerrainGeneratorFactory.hpp"

using std::string;

MapTimeObserver::MapTimeObserver()
{
}

void MapTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();

  // Get the current map.  
  MapPtr map = game.get_current_map();

  // Check to see if it can be updated with creatures
  if (map != nullptr && map->get_allow_creature_updates())
  {
    // The map can be updated.
    // Create the appropriate generator and call the update function.

    // JCD FIXME work probably needs to be done later for villages, worship sites, 
    // etc.  These require actual details from the tile - deity ID, village race
    // info, etc.  Once I want to get these updating, there will probably need to
    // be work done to pass the key details around in a map or something similar.
    TileType terrain_type = map->get_terrain_type();
    TilePtr null_tile;

    GeneratorPtr generator = TerrainGeneratorFactory::create_generator(null_tile, "", terrain_type);

    if (generator != nullptr)
    {
      generator->update_creatures(map, map->get_danger());
    }
  }
}

ITimeObserver* MapTimeObserver::clone() 
{
  return new MapTimeObserver(*this);
}

ClassIdentifier MapTimeObserver::internal_class_identifier() const
{
  return CLASS_ID_MAP_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapTimeObserver_test.cpp"
#endif

