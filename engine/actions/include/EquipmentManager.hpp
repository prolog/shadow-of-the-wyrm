#pragma once
#include "Creature.hpp"
#include "Display.hpp"
#include "IActionManager.hpp"

class EquipmentManager : public IActionManager
{
  public:
    ActionCostValue manage_equipment();

    // Assumption is that this function is only called for NPCs and the item
    // exists in the creature's inventory.
    ActionCostValue equip(CreaturePtr creature, ItemPtr i, const EquipmentWornLocation ewl);

    // This function should be called whenever a single equipment (or inventory)
    // item is required.  Equipping and unequipping is disallowed.
    ItemPtr select_item();

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    
    EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~EquipmentManager();

    DisplayPtr display;
    CreaturePtr creature;
};
