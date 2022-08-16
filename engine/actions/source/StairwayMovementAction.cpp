#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DigAction.hpp"
#include "DirectionUtils.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MapProperties.hpp"
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
  bool show_no_exit_message = false;

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

    if (map_exit == nullptr)
    {
      auto map_exits = current_map->get_map_exits();
      auto me_it = map_exits.find(Direction::DIRECTION_UP);

      if (me_it != map_exits.end())
      {
        if (MapUtils::can_exit_map(current_map, creature, me_it->second, Direction::DIRECTION_UP, c) == MapExitOutcome::CAN_EXIT)
        {
          map_exit = me_it->second;
        }
        else
        {
          string movement_message = StringTable::get(MovementTextKeys::ACTION_MOVE_OFF_BLOCKED);

          manager.add_new_message(movement_message);
          manager.send();

          return ascend_success;
        }
      }
    }
  
    if (map_exit)
    {
      if (map_exit->is_using_map_id())
      {
        if (MapUtils::can_change_zlevel(creature, current_map, tile, Direction::DIRECTION_UP))
        {
          move_to_custom_map(current_tile, current_map, map_exit, creature, game, ma, Direction::DIRECTION_UP);
          ascend_success = get_action_cost_value(creature);
        }
        else
        {
          show_no_exit_message = true;
        }
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
        string too_hard = StringTable::get(ActionTextKeys::ACTION_DIG_TOO_HARD);
        manager.add_new_message(too_hard);
        manager.send();
      }
    }
    else
    {
      if (MapUtils::can_change_zlevel(creature, current_map, tile, Direction::DIRECTION_UP))
      {
        ascend_success = generate_or_move_to_zlevel(game, ma, manager, creature, current_map, tile, c, map_exit, ExitMovementType::EXIT_MOVEMENT_ASCEND, Direction::DIRECTION_UP);
      }
      else
      {
        show_no_exit_message = true;
      }
    }

    if (show_no_exit_message)
    {
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
  bool show_no_exit_message = false;

  if (creature && creature->get_is_player())
  {
    // If we're on the world map, we can always descend.
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

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
        MapExitPtr map_exit;
        
        // If there is an exit in the down direction, do the appropriate action.
        if (t_it != exit_map.end())
        {
          MapExitPtr map_exit = t_it->second;

          if (map_exit)
          {
            if (map_exit->is_using_map_id())
            {
              if (MapUtils::can_change_zlevel(creature, map, tile, Direction::DIRECTION_DOWN))
              {
                move_to_custom_map(tile, map, map_exit, creature, game, ma, Direction::DIRECTION_DOWN);
                descend_success = get_action_cost_value(creature);
              }
              else
              {
                show_no_exit_message = true;
              }
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
            MapExitPtr map_exit = map->get_map_exit(Direction::DIRECTION_DOWN);

            if (MapUtils::can_change_zlevel(creature, map, tile, Direction::DIRECTION_DOWN))
            {
              descend_success = generate_or_move_to_zlevel(game, ma, manager, creature, map, tile, c, map_exit, ExitMovementType::EXIT_MOVEMENT_DESCEND, Direction::DIRECTION_DOWN);
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
                show_no_exit_message = true;
              }
            }
          }
        }  
      }

      if (show_no_exit_message)
      {
        string no_exit = StringTable::get(tile->get_no_exit_down_message_sid());
        manager.add_new_message(no_exit);

        manager.send();
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

void StairwayMovementAction::move_to_custom_map(TilePtr current_tile, MapPtr current_map, MapExitPtr map_exit, CreaturePtr creature, Game& game, MovementAction* const ma, const Direction d)
{
  if (creature != nullptr && current_map != nullptr && current_tile != nullptr)
  {
    Coordinate current_coord = current_map->get_location(creature->get_id());
    Coordinate proposed_new_coord = MapUtils::calculate_new_coord_for_multimap_movement(current_coord, current_tile, d, map_exit);
    
    ma->handle_properties_and_move(creature, current_tile, current_map, map_exit, proposed_new_coord);
  }
}

ActionCostValue StairwayMovementAction::generate_or_move_to_zlevel(Game& game, MovementAction* const ma, IMessageManager& manager, CreaturePtr creature, MapPtr map, TilePtr tile, const Coordinate& c, MapExitPtr map_exit, const ExitMovementType emt, const Direction d)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (map_exit == nullptr || MapUtils::can_exit_map(map, creature, map_exit, d, c) == MapExitOutcome::CAN_EXIT)
  {
    if (map_exit != nullptr && map_exit->is_using_map_id())
    {
      Coordinate old_c = map_exit->get_coordinate();
      map_exit->set_coordinate(c);
      move_to_custom_map(tile, map, map_exit, creature, game, ma, d);
      map_exit->set_coordinate(old_c);
      acv = get_action_cost_value(creature);
    }
    else
    {
      // Set the map as permanent so we can come back to it later.
      std::map<string, string> map_properties = { {MapProperties::MAP_PROPERTIES_PERMANENCE, std::to_string(true)} };
      map->set_permanent(true);
      tile->set_additional_property(TileProperties::TILE_PROPERTY_LINKED_COORD, MapUtils::convert_coordinate_to_map_key(c));
      acv = ma->generate_and_move_to_new_map(creature, map, nullptr, tile, tile->get_tile_type(), TileType::TILE_TYPE_UNDEFINED, map_properties, emt);

      MapPtr new_map = Game::instance().get_current_map();
      MapExitPtr new_map_linkage = std::make_shared<MapExit>();
      new_map_linkage->set_map_id(new_map->get_map_id());
      map->set_map_exit(d, new_map_linkage);

      MapExitPtr original_map_linkage = std::make_shared<MapExit>();
      original_map_linkage->set_map_id(map->get_map_id());
      new_map->set_map_exit(DirectionUtils::get_opposite_direction(d), original_map_linkage);

      if (map->get_map_type() == MapType::MAP_TYPE_UNDERWATER)
      {
        new_map->set_is_water_shallow(true);
      }
    }
  }
  else
  {
    string movement_message = StringTable::get(MovementTextKeys::ACTION_MOVE_OFF_BLOCKED);

    manager.add_new_message(movement_message);
    manager.send();
  }

  return acv;
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