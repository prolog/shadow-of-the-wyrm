#pragma once
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "EquipmentTypes.hpp"

class EquipmentTranslator
{
  public:
    static DisplayEquipmentMap create_display_equipment(const CreaturePtr& creature);

  protected:
    EquipmentTranslator();
    ~EquipmentTranslator();
};
