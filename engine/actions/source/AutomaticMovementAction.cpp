#include "ActionTextKeys.hpp"
#include "AutomaticMovementAction.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "AutomaticMovementFlags.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using std::string;

AutomaticMovementAction::AutomaticMovementAction()
{
}

ActionCostValue AutomaticMovementAction::automatic_movement(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  IMessageManager& manager = MM::instance();

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = std::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();

  // Initial check: are we on the world map?
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (creature != nullptr)
  {
    if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      creature->get_automatic_movement_ref().set_engaged(false);
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_AUTOMOVE_WORLD_MAP));
      manager.send();
    }
    else
    {
      AutomaticMovement& am = creature->get_automatic_movement_ref();
      bool added_initial_message = false;

      // If the creature is the player, inform the player that a direction is needed,
      // but only if automatic movement is not already engaged.
      if (creature->get_is_player() && !am.get_engaged())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
        manager.send();
        added_initial_message = true;
      }

      // Try to get a direction.
      //
      // If automatic movement is engaged, use the direction that has already been
      // selected.  Otherwise, prompt the creature.
      CommandPtr base_command;

      if (am.get_engaged())
      {
        base_command = std::make_shared<MovementCommand>(am.get_direction(), -1);
      }
      else
      {
        base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);
      }

      if (added_initial_message && creature->get_is_player())
      {
        manager.clear_if_necessary();
      }

      if (base_command)
      {
        std::shared_ptr<DirectionalCommand> dcommand;
        dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

        if (dcommand)
        {
          Direction d = dcommand->get_direction();

          if (d != Direction::DIRECTION_NULL)
          {
            action_cost_value = automatic_movement_in_direction(creature, map, d);
          }
          else
          {            
            action_cost_value = rest(creature);
          }
        }
      }
    }
  }

  return action_cost_value;
}

ActionCostValue AutomaticMovementAction::rest(CreaturePtr creature) const
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
  MapPtr map = Game::instance().get_current_map();
  IMessageManager& manager = MM::instance();

  // Start moving in the requested direction.
  AutomaticMovementCoordinator amc;

  if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
  {
    creature->get_automatic_movement_ref().set_engaged(false);
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_AUTOMOVE_WORLD_MAP));
    manager.send();
  }
  else
  {
    AutomaticMovementFlags amf(true, true, true, true);
    acv = amc.auto_move(creature, map, Direction::DIRECTION_NULL, amf);
  }

  return acv;
}

ActionCostValue AutomaticMovementAction::automatic_movement_in_direction(CreaturePtr creature, MapPtr map, const Direction d) const
{
  // Start moving in the requested direction.
  AutomaticMovementCoordinator amc;

  // The first time we auto-move, set the ignore flags.  This is so we can 
  // always move off the current tile.  For subsequent moves in the auto 
  // movement chain, the "engaged" flag will be set, and we'll properly
  // consider items, features, and so on, during the automatic movement
  // checks.
  bool ignore = !(creature->get_automatic_movement_ref().get_engaged());
  AutomaticMovementFlags amf(ignore, ignore, ignore, ignore);
  return amc.auto_move(creature, map, d, amf);
}

ActionCostValue AutomaticMovementAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
