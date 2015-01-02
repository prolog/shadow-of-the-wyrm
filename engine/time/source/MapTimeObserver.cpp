#include "Game.hpp"
#include "CreatureGenerationConstants.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapTimeObserver.hpp"
#include "MapUtils.hpp"
#include "TerrainGeneratorFactory.hpp"

using namespace std;

MapTimeObserver::MapTimeObserver()
{
}

void MapTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();

  // Get the current map.  
  MapPtr map = game.get_current_map();

  uint num_creatures = map->get_creatures().size();
  uint num_following = MapUtils::get_num_following_creatures(map);
  uint num_nonfollow = num_creatures - num_following;

  // Check to see if it can be updated with creatures
  if (map != nullptr && map->get_allow_creature_updates() && (num_nonfollow < CreatureGenerationConstants::MIN_CREATURES_FOR_MAP_UPDATE))
  {
    // The map can be updated.
    // Create the appropriate generator and call the update function.
    MapCreatureGenerator mcg;

    std::map<string, string> props;
    mcg.generate_random_creatures(map, map->get_danger(), props);
  }
}

ITimeObserver* MapTimeObserver::clone() 
{
  return new MapTimeObserver(*this);
}

ClassIdentifier MapTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapTimeObserver_test.cpp"
#endif

