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
    static Resistances calculate_resistances(const Creature& creature, RacePtr race, ClassPtr char_class);

  protected:
    ResistancesCalculator();
    ~ResistancesCalculator();
};
