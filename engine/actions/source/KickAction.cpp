#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "KickAction.hpp"

using std::string;

KickAction::KickAction()
{
}

ActionCostValue KickAction::kick(CreaturePtr creature)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    CurrentCreatureAbilities cca;

    string kick_msg;
    
    if (cca.can_move(creature))
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();
      MapType map_type = current_map->get_map_type();

      if (map_type == MAP_TYPE_WORLD)
      {
        acv = kick_on_world_map(creature, current_map);
      }
      else
      {
        acv = kick_on_regular_map(creature, current_map);
      }
    }
  }
  
  return acv;
}

// Kicking on the world map doesn't do anything, but should display a message
// nonetheless.
ActionCostValue KickAction::kick_on_world_map(CreaturePtr creature, MapPtr current_map)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    string kick_msg = StringTable::get(ActionTextKeys::ACTION_KICK_WORLD_MAP);
    manager.add_new_message(kick_msg);
    manager.send();
  }

  return 0;
}

// Handle kicking on a regular map: prompt the creature for a direction, then go from there.
ActionCostValue KickAction::kick_on_regular_map(CreaturePtr creature, MapPtr current_map)
{
  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    // If the creature is the player, get the kicking direction.
    if (creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
      manager.send();
    }

    // Try to get a direction.
    //
    // If automatic movement is engaged, use the direction that has already been
    // selected.  Otherwise, prompt the creature.
    CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
    KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();
    CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

    if (base_command)
    {
      std::shared_ptr<DirectionalCommand> dcommand;
      dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

      if (dcommand)
      {
        return kick_in_direction(creature, current_map, dcommand->get_direction());
      }
    }
  }

  return 0;
}

// Kick in a particular direction on a regular map.
ActionCostValue KickAction::kick_in_direction(CreaturePtr creature, MapPtr current_map, const Direction direction)
{
  ActionCostValue acv = 0;

  if (creature && current_map)
  {
    TilePtr kick_tile = MapUtils::get_adjacent_tile(current_map, creature, direction);
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    if (kick_tile)
    {
      acv = get_action_cost_value(creature);

      manager.add_new_message(ActionTextKeys::get_kick_message(creature->get_description_sid(), creature->get_is_player()));

      // Is there a creature?
      if (kick_tile->has_creature())
      {
      }
      // No creature to kick.  Is there a feature?
      else if (kick_tile->has_feature())
      {
      }
      else
      {
        // Creatures can't kick solid tiles, unless they're incorporeal, or can
        // otherwise pass through such things.
        if (kick_tile->get_movement_multiplier() == 0 && !creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
        {
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SOLID_TILE));
        }
        // Kicking a water tile generates a message
        else if (kick_tile->get_tile_super_type() == TILE_SUPER_TYPE_WATER)
        {
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_WATER_TILE));
        }
        else
        {
          // ...
        }
      }
    }
    else
    {
      if (creature->get_is_player())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_NOTHING_TO_KICK_AT));
        manager.send();
      }
    }

    manager.send();
  }

  return acv;
}

ActionCostValue KickAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

