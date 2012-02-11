#pragma once
#include <map>
#include "Creature.hpp"
#include "DisplayItem.hpp"
#include "EquipmentTypes.hpp"

typedef std::map<EquipmentWornLocation, DisplayItem> DisplayEquipmentMap;

class EquipmentTranslator
{
  public:
    static DisplayEquipmentMap create_display_equipment(const CreaturePtr& creature);

  protected:
    EquipmentTranslator();
    ~EquipmentTranslator();
};
