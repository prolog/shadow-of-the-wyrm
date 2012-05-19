#include "Resistances.hpp"
#include "ResistancesCalculator.hpp"

ResistancesCalculator::ResistancesCalculator()
{
}

ResistancesCalculator::~ResistancesCalculator()
{
}

Resistances ResistancesCalculator::default_resistances()
{
  Resistances resists;
  
  for (DamageType dt = DAMAGE_TYPE_SLASH; dt < DAMAGE_TYPE_MAX; dt++)
  {
    double value = DEFAULT_RESISTANCE_VALUE;
    resists.set_resistance_value(dt, value );
  }
  
  return resists;
}

Resistances ResistancesCalculator::calculate_resistances(const Creature& creature, RacePtr race, ClassPtr cur_class)
{
  Resistances resists_calculated;

  if (race && cur_class)
  {
    Resistances resists_race  = race->get_resistances();
    Resistances resists_class = cur_class->get_resistances(); 
    double race_val  = 0.0;
    double class_val = 0.0;
    double total_val = 0.0;

    for (DamageType dt = DAMAGE_TYPE_SLASH; dt < DAMAGE_TYPE_MAX; dt++)
    {
      race_val  = resists_race.get_resistance_value(dt);
      class_val = resists_class.get_resistance_value(dt);
      
      total_val = race_val + class_val;
      
      resists_calculated.set_resistance_value(dt, total_val);
    }
  }

  // JCD FIXME: Include resistances from worn equipment.

  return resists_calculated;
}

#ifdef UNIT_TESTS
#include "unit_tests/ResistancesCalculator_test.cpp"
#endif
