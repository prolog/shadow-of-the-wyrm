#include "Conversion.hpp"
#include "DeityTextKeys.hpp"
#include "MapProperties.hpp"
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
ActionCostValue PietyAction::piety(CreaturePtr creature, MapPtr map, ActionManager * const am) const
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance();

    if (String::to_bool(map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY)))
    {
      manager.add_new_message(StringTable::get(DeityTextKeys::DEITY_CANNOT_PRAY));
    }
    else
    {
      // Get the piety.
      ReligionManager rm;
      int piety = rm.get_piety_for_active_deity(creature);

      manager.add_new_message(SacrificeTextKeys::get_piety_message(piety));
    }

    manager.send();
  }

  return get_action_cost_value(creature);
}

// Checking piety is a free action.
ActionCostValue PietyAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
