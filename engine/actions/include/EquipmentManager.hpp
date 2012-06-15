#pragma once
#include "Creature.hpp"
#include "Display.hpp"
#include "IActionManager.hpp"

class EquipmentManager : public IActionManager
{
  public:
    EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature);
    ~EquipmentManager();

    bool manage_equipment();

  protected:
    uint get_current_action_cost() const;

    DisplayPtr display;
    CreaturePtr creature;
};
