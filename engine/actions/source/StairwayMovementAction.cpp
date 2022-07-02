#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementTextKeys.hpp"
#include "RockTile.hpp"
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
  ActionCostValue ascend_success = ActionCostConstants::NO_ACTION;
  
  if (creature->get_is_player())
  {
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    
    MapPtr current_map = game.get_current_map();
    Coordinate c = current_map->get_location(creature->get_id());
    TilePtr tile = current_map->at(c);

    // Otherwise, check to see if the creature is on a tile with DIRECTION_UP defined.
    TilePtr current_tile = MapUtils::get_tile_for_creature(current_map, creature);
    TileExitMap& tile_exit_map = current_tile->get_tile_exit_map_ref();
    TileExitMap::iterator t_it = tile_exit_map.find(Direction::DIRECTION_UP);
    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    string dig_hardness;
    RockTile rock_tile;

    if (wielded != nullptr)
    {
      dig_hardness = wielded->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS);
    }

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
        ascend_success = ma->generate_and_move_to_new_map(creature, current_map, map_exit, current_tile, map_exit->get_terrain_type(), current_tile->get_tile_subtype(), map_exit->get_properties(), ExitMovementType::EXIT_MOVEMENT_ASCEND);
      }
    }
    else if (current_map->get_map_type() == MapType::MAP_TYPE_UNDERWORLD &&
             !dig_hardness.empty())
    {
      if (String::to_int(dig_hardness) >= rock_tile.get_hardness())
      {
        // Dig into the ceiling, scattering stones everywhere.
        DigAction da;
        ascend_success = da.dig_ceiling(creature, current_map);
      }
      else
      {
        IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
        string too_hard = StringTable::get(ActionTextKeys::ACTION_DIG_TOO_HARD);
        manager.add_new_message(too_hard);
        manager.send();
      }
    }
    else
    {
      // Let the player know there is no exit.
      string no_exit = StringTable::get(tile->get_no_exit_up_message_sid());
          
      manager.add_new_message(no_exit);
      manager.send();                
    }
  }
  else
  {
    Log::instance().log("StairwayMovementAction::ascend - Trying to ascend with non-player creature.  Not supported yet.");
  }
  
  return ascend_success;
}

ActionCostValue StairwayMovementAction::descend(CreaturePtr creature, MovementAction * const ma)
{
  ActionCostValue descend_success = ActionCostConstants::NO_ACTION;
   
  if (creature && creature->get_is_player())
  {
    // If we're on the world map, we can always descend.
    Game& game = Game::instance();
    
    MapPtr map = game.get_current_map();
    ExitMovementType movement_type = ExitMovementType::EXIT_MOVEMENT_DESCEND;

    if (map)
    {
      // Look up the creature in the map
      Coordinate c = map->get_location(creature->get_id());
      
      // Get the creature's tile's MapExitPtr
      TilePtr tile = map->at(c);
        
      if (tile)
      {
        TileExitMap& exit_map = tile->get_tile_exit_map_ref();
        TileExitMap::const_iterator t_it = exit_map.find(Direction::DIRECTION_DOWN);
        
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
              descend_success = ma->generate_and_move_to_new_map(creature, map, map_exit, tile, map_exit->get_terrain_type(), tile->get_tile_subtype(), map_exit->get_properties(), movement_type);
            }
          }
          else
          {
            descend_success = ma->generate_and_move_to_new_map(creature, map, nullptr, tile, movement_type);
          }
        }
        // If it's null, check to see if we're on the world map.
        else
        {
          MapType map_type = map->get_map_type();
            
          if (map_type == MapType::MAP_TYPE_WORLD)
          {
            descend_success = ma->generate_and_move_to_new_map(creature, map, nullptr, tile, ExitMovementType::EXIT_MOVEMENT_DESCEND);
          }
          else
          {
            // Does the creature have something to dig with?
            ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
            if (wielded != nullptr && wielded->has_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS))
            {
              DigAction da;
              descend_success = da.dig_within(creature, wielded, map, tile);
            }
            else
            {
              IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
              string no_exit = StringTable::get(tile->get_no_exit_down_message_sid());
              manager.add_new_message(no_exit);

              manager.send();
            }
          }
        }  
      }
    }

    // Once we've descended, see if the new depth's current value is greater
    // than what the creature currently has.  If so, track it.
    MapPtr new_map = game.get_current_map();

    if (new_map != nullptr)
    {
      Depth d = new_map->size().depth();

      if (d.get_current() > creature->get_max_depth_reached().get_current())
      {
        creature->set_max_depth_reached(d);
      }
    }
  }
  else
  {
    Log::instance().log("StairwayMovementAction::descend - Trying to descend with non-player creature.  Not supported yet.");    
  }
  
  return descend_success;
}

void StairwayMovementAction::move_to_custom_map(TilePtr current_tile, MapPtr current_map, MapExitPtr map_exit, CreaturePtr creature, Game& game, MovementAction* const ma)
{
  // JCD FIXME: For now, stairway movement isn't part of multi-map movement
  // (assume everything's on the same rough z-level), so pass in a null
  // coordinate to allow the game to use either the pre-set location,
  // or the pre-existing one.
  ma->handle_properties_and_move(creature, current_tile, current_map, map_exit, CoordUtils::end());
}

ActionCostValue StairwayMovementAction::get_action_cost_value(CreaturePtr creature) const
{
  ActionCostValue acv = ActionCostConstants::DEFAULT;

  if (creature != nullptr)
  {
    if (creature->has_status(StatusIdentifiers::STATUS_ID_TIMEWALK))
    {
      acv = 0;
    }
  }

  return acv;
}