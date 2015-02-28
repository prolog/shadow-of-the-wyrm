#include "MessageManagerFactory.hpp"
#include "PietyAction.hpp"
#include "ReligionManager.hpp"
#include "SacrificeTextKeys.hpp"

using namespace std;

PietyAction::PietyAction()
{
}

// Check to see how pious the creature is, displaying a message with
// the result.
ActionCostValue PietyAction::piety(CreaturePtr creature, ActionManager * const am) const
{
  if (creature != nullptr)
  {
    // Get the piety.
    ReligionManager rm;
    int piety = rm.get_piety_for_active_deity(creature);

    // Create a message about the piety level.
    if (creature->get_is_player())
    {
      IMessageManager& manager = MessageManagerFactory::instance();
      manager.add_new_message(SacrificeTextKeys::get_piety_message(piety));
      manager.send();
    }
  }

  return get_action_cost_value(creature);
}

// Checking piety is a free action.
ActionCostValue PietyAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
