#pragma once
#include <map>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"

class EquipmentScreen : public Screen
{
  public:
    EquipmentScreen(DisplayPtr display, CreaturePtr creature);

  protected:
    void initialize() override;
    CreaturePtr creature;
};
