#include "Game.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "StairwayMovementManager.hpp"

using namespace std;

StairwayMovementManager::StairwayMovementManager()
{
}

StairwayMovementManager::~StairwayMovementManager()
{
}

ActionCostValue StairwayMovementManager::ascend(CreaturePtr creature, MovementManager * const mm)
{
  ActionCostValue ascend_success = 0;
  
  if (creature->get_is_player())
  {
    Game* game = Game::instance();
    MessageManager* manager = MessageManager::instance();
    
    if (game)
    {
      MapPtr current_map = game->get_current_map();

      // Otherwise, check to see if the creature is on a tile with DIRECTION_UP defined.
      TilePtr current_tile = MapUtils::get_tile_for_creature(current_map, creature);
      TileExitMap& tile_exit_map = current_tile->get_tile_exit_map_ref();
      TileExitMap::iterator t_it = tile_exit_map.find(DIRECTION_UP);
      
      MapExitPtr map_exit;
      
      if (t_it != tile_exit_map.end())
      {
        map_exit = t_it->second;        
      }
  
      if (map_exit)
      {
        if (map_exit->is_using_map_id())
        {
          mm->move_to_new_map(current_tile, current_map, map_exit);
        
          // If the tile we've moved to has any items, notify the player, if the creature's a player.
          MapPtr new_map = game->get_current_map();

          TilePtr creatures_current_tile = MapUtils::get_tile_for_creature(new_map, creature);
          mm->add_message_about_items_on_tile_if_necessary(creature, manager, creatures_current_tile);
        
          ascend_success = get_action_cost_value();
        }
        else
        {
          ascend_success = mm->generate_and_move_to_new_map(creature, current_map, current_tile, -1);
        }
      }
      else
      {
        // This is so that it's easy to find/replace this later, once I add message managers
        // per-creature
        if (creature->get_is_player())
        {
          // Let the player know there is no exit.
          string no_exit = StringTable::get(MovementTextKeys::ACTION_MOVE_NO_EXIT);
          
          manager->add_new_message(no_exit);
          manager->send();                
        }
      }
    }
  }
  else
  {
    Log* log = Log::instance();
    log->log("Trying to ascend with non-player creature.  Not supported yet.");
  }
  
  return ascend_success;
}

ActionCostValue StairwayMovementManager::descend(CreaturePtr creature, MovementManager * const mm)
{
  ActionCostValue descend_success = 0;
 
  MessageManager* manager = MessageManager::instance();
  
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
        Coordinate c = map->get_location(creature->get_id());
      
        // Get the creature's tile's MapExitPtr
        TilePtr tile = map->at(c);
        
        if (tile)
        {
          TileExitMap& exit_map = tile->get_tile_exit_map_ref();
          TileExitMap::const_iterator t_it = exit_map.find(DIRECTION_DOWN);
        
          // If there is an exit in the down direction, do the appropriate action.
          if (t_it != exit_map.end())
          {
            descend_success = mm->generate_and_move_to_new_map(creature, map, tile, 1);
          }
          // If it's null, check to see if we're on the world map.
          else
          {
            MapType map_type = map->get_map_type();
            
            if (map_type == MAP_TYPE_WORLD)
            {
              descend_success = mm->generate_and_move_to_new_map(creature, map, tile, 1);
            }
            else
            {
              // This is so that it's easy to find/replace this later, once I add message managers
              // per-creature
              if (creature->get_is_player())
              {
                // Let the player know there is no exit.
                string no_exit = StringTable::get(MovementTextKeys::ACTION_MOVE_NO_EXIT);
                
                manager->add_new_message(no_exit);
                manager->send();                
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

ActionCostValue StairwayMovementManager::get_action_cost_value() const
{
  return 1;
}