#include "Conversion.hpp"
#include "MovementManager.hpp"

using namespace std;

MovementManager::MovementManager()
{
}

MovementManager::~MovementManager()
{
}

void MovementManager::set_current_map(MapPtr new_map)
{
  map = new_map;
}

void MovementManager::move(CreaturePtr creature, const Direction direction)
{
  if (creature)
  {
    // Get the creature's location from the map
    string s_id = Uuid::to_string(creature->get_id());
    Coordinate c = map->get_location(s_id);

    // Based on the direction, get the tile to which to move.
  }
}
