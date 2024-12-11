#include "Conversion.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
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
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance();

    if (String::to_bool(map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY)))
    {
      manager.add_new_message(StringTable::get(DeityTextKeys::DEITY_CANNOT_PRAY));
    }
    else
    {
      const DeityMap& deities = game.get_deities_ref();

      if (!deities.empty())
      {
        check_piety(creature, manager);
      }
      else
      {
        remove_all_piety(creature, manager);
      }
    }
  }

  return get_action_cost_value(creature);
}

void PietyAction::check_piety(CreaturePtr creature, IMessageManager& manager) const
{
  if (creature != nullptr && !creature->is_godless())
  {
    ReligionManager rm;
    int piety = rm.get_piety_for_active_deity(creature);

    manager.add_new_message(SacrificeTextKeys::get_piety_message(piety));
    manager.send();
  }
}

void PietyAction::remove_all_piety(CreaturePtr creature, IMessageManager& manager) const
{
  if (creature != nullptr)
  {
    Religion& religion = creature->get_religion_ref();
    DeityRelations& rel = religion.get_deity_relations_ref();
    rel.clear();

    manager.add_new_message(StringTable::get(SacrificeTextKeys::SACRIFICE_PIETY_NO_DEITIES));
    manager.send();
  }
}

// Checking piety is a free action.
ActionCostValue PietyAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}
