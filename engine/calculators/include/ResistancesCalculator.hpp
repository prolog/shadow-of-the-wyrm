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
    Resistances calculate_resistances(CreaturePtr creature, RacePtr race, ClassPtr char_class);
    Resistances calculate_race_and_class_resistances(CreaturePtr creature, RacePtr race, ClassPtr cur_class);

  protected:
    Resistances calculate_equipment_resistances(CreaturePtr creature);
};
