#include "Conversion.hpp"
#include "MessageManager.hpp"
#include "MovementManager.hpp"
#include "MapUtils.hpp"

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
    Coordinate creature_location = map->get_location(s_id);

    // Get the old tile
    TilePtr creatures_old_tile = map->at(creature_location.first, creature_location.second);

    // Is the proposed movement valid?
    // If it is not, and the creature is the player, display a message.
    // Otherwise, move the creature.
    if (!MapUtils::is_valid_move(map->size(), creature_location, direction))
    {
      if (creature->get_is_player())
      {
        MessageManager* manager = MessageManager::instance();
        // JCD FIXME: Check to see if the map is the world map.  If it isn't, get a different message.
        string movement_message = StringTable::get(ActionTextKeys::ACTION_MOVE_OFF_WORLD_MAP);

        manager->add_new_message(movement_message);
        manager->send();
      }
    }
    else
    {
      Coordinate new_coords = MapUtils::get_new_coordinate(creature_location, direction);
      TilePtr creatures_new_tile = map->at(new_coords.first, new_coords.second);

      // Can the creature be added to the new tile?
      if (creatures_new_tile && !creatures_new_tile->has_creature())
      {
        creatures_old_tile->remove_creature();
        creatures_new_tile->set_creature(creature);

        // Update the quick-find location on map.
        map->add_or_update_location(s_id, new_coords);

        if (creature->get_is_player())
        {
          map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, new_coords);
        }
      }
    }
  }
}
