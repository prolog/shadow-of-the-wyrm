#include "Game.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementTextKeys.hpp"
#include "StairwayMovementAction.hpp"

using namespace std;

StairwayMovementAction::StairwayMovementAction()
{
}

StairwayMovementAction::~StairwayMovementAction()
{
}

ActionCostValue StairwayMovementAction::ascend(CreaturePtr creature, MovementAction * const ma)
{
  ActionCostValue ascend_success = 0;
  
  if (creature->get_is_player())
  {
    Game& game = Game::instance();
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    
    MapPtr current_map = game.get_current_map();

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
        move_to_custom_map(current_tile, current_map, map_exit, creature, game, ma);        
        ascend_success = get_action_cost_value(creature);
      }
      else
      {
        ascend_success = ma->generate_and_move_to_new_map(creature, current_map, current_tile, -1);
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
          
        manager.add_new_message(no_exit);
        manager.send();                
      }
    }
  }
  else
  {
    Log::instance().log("Trying to ascend with non-player creature.  Not supported yet.");
  }
  
  return ascend_success;
}

ActionCostValue StairwayMovementAction::descend(CreaturePtr creature, MovementAction * const ma)
{
  ActionCostValue descend_success = 0;
 
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature->get_is_player())
  {
    // If we're on the world map, we can always descend.
    Game& game = Game::instance();
    
    MapPtr map = game.get_current_map();

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
          MapExitPtr map_exit = t_it->second;

          if (map_exit)
          {
            if (map_exit->is_using_map_id())
            {
              move_to_custom_map(tile, map, map_exit, creature, game, ma);        
              descend_success = get_action_cost_value(creature);
            }
            else
            {
              descend_success = ma->generate_and_move_to_new_map(creature, map, tile, 1);
            }
          }
          else
          {
            descend_success = ma->generate_and_move_to_new_map(creature, map, tile, 1);
          }
        }
        // If it's null, check to see if we're on the world map.
        else
        {
          MapType map_type = map->get_map_type();
            
          if (map_type == MAP_TYPE_WORLD)
          {
            descend_success = ma->generate_and_move_to_new_map(creature, map, tile, 1);
          }
          else
          {
            // This is so that it's easy to find/replace this later, once I add message managers
            // per-creature
            if (creature->get_is_player())
            {
              // Let the player know there is no exit.
              string no_exit = StringTable::get(MovementTextKeys::ACTION_MOVE_NO_EXIT);
                
              manager.add_new_message(no_exit);
              manager.send();                
            }
          }
        }  
      }
    }
  }
  else
  {
    Log::instance().log("Trying to descend with non-player creature.  Not supported yet.");    
  }
  
  return descend_success;
}

void StairwayMovementAction::move_to_custom_map(TilePtr current_tile, MapPtr current_map, MapExitPtr map_exit, CreaturePtr creature, Game& game, MovementAction* const ma)
{
  ma->handle_properties_and_move_to_new_map(current_tile, current_map, map_exit);

  // If the tile we've moved to has any items, notify the player, if the creature's a player.
  MapPtr new_map = game.get_current_map();

  TilePtr creatures_current_tile = MapUtils::get_tile_for_creature(new_map, creature);
  ma->add_message_about_items_on_tile_if_necessary(creature, creatures_current_tile);
}

ActionCostValue StairwayMovementAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}