#include "PapercraftSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

ActionCostValue PapercraftSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature && map)
  {
    if (check_for_equipment(creature))
    {
      // ...
    }
  }

  return acv;
}

// Check to 
bool PapercraftSkillProcessor::check_for_equipment(CreaturePtr creature)
{
  bool has_eq = false;

  if (creature != nullptr)
  {
    IMessageManager& manager = MessageManagerFactory::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    ItemPtr off_hand = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);
    string check_id = ItemIdKeys::ITEM_ID_MOLD_AND_DECKLE;

    if ((wielded && wielded->get_base_id() == check_id) ||
        (off_hand && off_hand->get_base_id() == check_id))
    {
      has_eq = true;
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PAPERCRAFT_NO_EQUIPMENT));
      manager.send();

      return false;
    }

    check_id = ItemIdKeys::ITEM_ID_PAPER_PULP;

    if (creature->get_inventory()->get_from_base_id(check_id) != nullptr)
    {
      has_eq = true;
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PAPERCRAFT_NO_PULP));
      manager.send();

      return false;
    }
  }

  return has_eq;
}

ActionCostValue PapercraftSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return -1;
}