#include "ActionTextKeys.hpp"
#include "AutomaticMovementAction.hpp"
#include "AutomaticMovementCoordinator.hpp"
#include "Commands.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using std::string;

AutomaticMovementAction::AutomaticMovementAction()
{
}

ActionCostValue AutomaticMovementAction::automatic_movement(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;
  IMessageManager& manager = MessageManagerFactory::instance();

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // Initial check: are we on the world map?
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (map->get_map_type() == MAP_TYPE_WORLD)
  {
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
      base_command = boost::make_shared<MovementCommand>(am.get_direction());
    }
    else
    {
      base_command = creature->get_decision_strategy()->get_nonmap_decision(creature->get_id(), command_factory, kb_command_map, 0);
    }

    if (added_initial_message && creature->get_is_player())
    {
      manager.clear_if_necessary();
    }

    if (base_command)
    {
      boost::shared_ptr<DirectionalCommand> dcommand;
      dcommand = boost::dynamic_pointer_cast<DirectionalCommand>(base_command);

      if (dcommand)
      {
        Game& game = Game::instance();
        MapPtr map = game.get_current_map();

        action_cost_value = get_action_cost_value();
        Direction d = dcommand->get_direction();

        // Start moving in the requested direction.
        AutomaticMovementCoordinator amc;
        action_cost_value = amc.auto_move(creature, map, d);
      }
    }
  }

  return action_cost_value;
}

ActionCostValue AutomaticMovementAction::get_action_cost_value() const
{
  return 1;
}

