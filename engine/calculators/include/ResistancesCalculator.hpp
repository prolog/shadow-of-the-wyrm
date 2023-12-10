#pragma once
#include "Class.hpp"
#include "Creature.hpp"
#include "Race.hpp"

class Resistances;

// Used to calculate a total set of resistances, based on race, class,
// and currently worn equipment.
class ResistancesCalculator
{
  public:
    Resistances default_resistances();
    Resistances calculate_resistances(CreaturePtr creature, Race* race, Class* char_class);
    Resistances calculate_non_equipment_resistances(CreaturePtr creature, Race* race, Class* cur_class);

  protected:
    Resistances calculate_equipment_resistances(CreaturePtr creature);
    Resistances calculate_modifier_resistances(CreaturePtr creature);

    static const double GODLESSNESS_HOLY_RESISTANCE_VAL;
};
