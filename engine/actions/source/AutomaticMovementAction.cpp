#include "ActionTextKeys.hpp"
#include "AutomaticMovementAction.hpp"
#include "Commands.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"

using std::string;

AutomaticMovementAction::AutomaticMovementAction()
{
}

ActionCostValue AutomaticMovementAction::automatic_movement(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = 0;

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
    manager.send();
  }

  // Try to get a direction.
  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(creature->get_id(), command_factory, kb_command_map, 0);

  if (base_command)
  {
    boost::shared_ptr<DirectionalCommand> dcommand;
    dcommand = boost::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      action_cost_value = get_action_cost_value();
      Direction d = dcommand->get_direction();

      // Start moving in the requested direction.
      AutomaticMovement am(d, true);
      creature->set_automatic_movement(am);

      MovementAction maction;
      action_cost_value = maction.move(creature, d);

      // If the creature wasn't able to move, disengage automovement.
      if (action_cost_value == 0)
      {
        am.set_engaged(false);
      }
    }
  }

  return action_cost_value;
}

ActionCostValue AutomaticMovementAction::get_action_cost_value() const
{
  return 1;
}

