#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MessageManager.hpp"
#include "MovementManager.hpp"
#include "MapUtils.hpp"
#include "TerrainGeneratorFactory.hpp"

using namespace std;
using boost::make_shared;

MovementManager::MovementManager()
{
}

MovementManager::~MovementManager()
{
}

bool MovementManager::move(CreaturePtr creature, const Direction direction)
{
  bool movement_success = false;
  Game* game = Game::instance();
  
  if (creature && game)
  {
    MapPtr map = game->get_current_map();
    
    // Get the creature's location from the map
    string s_id = Uuid::to_string(creature->get_id());
    Coordinate creature_location = map->get_location(s_id);

    // Get the old tile
    TilePtr creatures_old_tile = map->at(creature_location.first, creature_location.second);

    // Is the proposed movement valid?
    // If it is not, and there is no map exit, and the creature is the player, display a message.
    // Otherwise, move the creature.
    if (!MapUtils::is_valid_move(map->size(), creature_location, direction))
    {
      MapExitPtr map_exit = map->get_map_exit();
      
      if (!MapUtils::can_exit_map(map_exit))
      {
        if (creature->get_is_player())
        {
          MessageManager* manager = MessageManager::instance();
 
          string movement_message = StringTable::get(ActionTextKeys::ACTION_MOVE_OFF_WORLD_MAP);

          manager->add_new_message(movement_message);
          manager->send();
        }
      }
      else
      {
        if (creature->get_is_player())
        {
          string leave_area = TextMessages::get_confirmation_message(TextKeys::DECISION_LEAVE_AREA);
          game->display->confirm(leave_area);
        }
        
        if (creature->get_decision_strategy()->get_confirmation())
        {
          move_to_new_map(map_exit);
          movement_success = true;
        }
        
        // Regardless of whether we leave the map or not, clear the messages, so the text doesn't hang around.
        game->display->clear_messages();
      }
    }
    // Otherwise, it's a regular move within the current map.
    else
    {
      Coordinate new_coords = MapUtils::get_new_coordinate(creature_location, direction);
      TilePtr creatures_new_tile = map->at(new_coords.first, new_coords.second);

      // Can the creature be added to the new tile?
      if (creatures_new_tile && !creatures_new_tile->has_creature())
      {
        // Update the map info
        MapUtils::add_or_update_location(map, creature, new_coords, creatures_old_tile);
        movement_success = true;
      }
    }
  }
  
  return movement_success;
}

void MovementManager::move_to_new_map(MapPtr new_map)
{
  Game* game = Game::instance();
  
  if (game && new_map)
  {
    game->set_current_map(new_map);
    game->reload_map();    
  }
}

void MovementManager::move_to_new_map(MapExitPtr map_exit)
{
  Game* game = Game::instance();
  
  if (game && map_exit)
  {
    if (map_exit->is_using_map_id())
    {
      string new_map_id = map_exit->get_map_id();
      MapPtr new_map = game->map_registry.get_map(new_map_id);
      
      move_to_new_map(new_map);
    }
    else
    {
      // A random terrain map.
      // JCD FIXME fill this in later.
    }
  }
}

bool MovementManager::ascend(CreaturePtr creature)
{
  bool ascend_success = false;
  
  if (creature->get_is_player())
  {
    Game* game = Game::instance();
    
    if (game)
    {
      MapPtr current_map = game->get_current_map();
      MapExitPtr map_exit = current_map->get_map_exit();
      
      move_to_new_map(map_exit);
      ascend_success = true;
    }
  }
  else
  {
    Log* log = Log::instance();
    log->log("Trying to ascend with non-player creature.  Not supported yet.");
  }
  
  return ascend_success;
}

bool MovementManager::descend(CreaturePtr creature)
{
  bool descend_success = false;
  
  if (creature->get_is_player())
  {
    // If we're on the world map, we can always descend.
    Game* game = Game::instance();
    
    if (game)
    {
      MapPtr map = game->get_current_map();

      if (map)
      {
        // Look up the creature in the map
        Coordinate c = map->get_location(Uuid::to_string(creature->get_id()));
      
        // Get the creature's tile's MapExitPtr
        TilePtr tile = map->at(c);
        
        if (tile)
        {
          TileExitMap& exit_map = tile->get_tile_exit_map_ref();
          TileExitMap::const_iterator t_it = exit_map.find(DIRECTION_DOWN);
        
          // If there is an exit in the down direction, do the appropriate action.
          if (t_it != exit_map.end())
          {
            // JCD FIXME Fill this in later.
            descend_success = true;
          }
          // If it's null, check to see if we're on the world map.
          else
          {
            MapType map_type = map->get_map_type();
            
            if (map_type == MAP_TYPE_WORLD)
            {
              TileType tile_type = tile->get_tile_type();
              GeneratorPtr generator = TerrainGeneratorFactory::create_generator(tile_type);
              
              if (generator)
              {
                // - Generate the map.
                MapPtr new_map = generator->generate();
                
                // - Set the map's MapExitPtr to point to the overworld.
                MapExitPtr new_map_exit = make_shared<MapExit>();
                new_map_exit->set_map_id(map->get_map_id());
                new_map->set_map_exit(new_map_exit);
                
                Coordinate starting_coords(0,0);
                MapUtils::add_or_update_location(new_map, creature, starting_coords);

                move_to_new_map(new_map);
                
                MessageManager* manager = MessageManager::instance();
                manager->add_new_message(TextMessages::get_area_entrance_message_given_terrain_type(tile_type));
                manager->send();
                
                descend_success = true;
              }
            }
          }        
        }
      }
    }
  }
  else
  {
    Log* log = Log::instance();
    log->log("Trying to descend with non-player creature.  Not supported yet.");    
  }
  
  return descend_success;
}
