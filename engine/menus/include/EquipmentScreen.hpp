#pragma once
#include <map>
#include "Creature.hpp"
#include "Menu.hpp"
#include "Display.hpp"

class EquipmentScreen : public Menu
{
  public:
    EquipmentScreen(DisplayPtr display, CreaturePtr creature);

  protected:
    void initialize() override;
    CreaturePtr creature;
};
