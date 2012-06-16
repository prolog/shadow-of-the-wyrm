#pragma once
#include "Creature.hpp"
#include "Display.hpp"
#include "IActionManager.hpp"

class EquipmentManager : public IActionManager
{
  public:

    ActionCostValue manage_equipment();

  protected:
    friend class ActionManager;
    
    EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~EquipmentManager();

    ActionCostValue get_action_cost_value() const;

    DisplayPtr display;
    CreaturePtr creature;
};
