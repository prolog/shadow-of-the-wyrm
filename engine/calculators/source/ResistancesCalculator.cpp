#include "Resistances.hpp"
#include "ResistancesCalculator.hpp"

Resistances ResistancesCalculator::default_resistances()
{
  Resistances resists;
  
  for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
  {
    double value = DEFAULT_RESISTANCE_VALUE;
    resists.set_resistance_value(dt, value );
  }
  
  return resists;
}

Resistances ResistancesCalculator::calculate_resistances(CreaturePtr creature, RacePtr race, ClassPtr cur_class)
{
  Resistances resists_calculated;
  Resistances resists_eq = calculate_equipment_resistances(creature);

  double raceclass_val  = 0.0;
  double eq_val         = 0.0;
  double total_val      = 0.0;

  Resistances resists_raceclass = calculate_race_and_class_resistances(creature, race, cur_class);

  for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
  {
    // A positive value (e.g., 0.25) means increased resistance.
    // Since the resistance is a multiplier, to increase resistance,
    // we subtract the value from 1 to get a value less than 1,
    // which will in turn reduce damage.
    raceclass_val = resists_raceclass.get_resistance_value(dt);
    eq_val        = resists_eq.get_resistance_value(dt);
    total_val     = 1 - (eq_val + raceclass_val);
      
    resists_calculated.set_resistance_value(dt, total_val);
  }

  return resists_calculated;
}

// Calculate the creature's combined race and class resistances.
Resistances ResistancesCalculator::calculate_race_and_class_resistances(CreaturePtr creature, RacePtr race, ClassPtr cur_class)
{
  Resistances res;
  res.set_all_resistances_to(0);

  if (creature)
  {
    // Since race and class may be optional, add guards to ensure that we're
    // only using them when defined, using 0 for each res otherwise...
    Resistances race_res;
    race_res.set_all_resistances_to(0);
    
    if (race)
    {
      race_res = race->get_resistances();
    }

    Resistances class_res;
    class_res.set_all_resistances_to(0);

    if (cur_class)
    {
      class_res = cur_class->get_resistances();
    }

    for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
    {
      res.set_resistance_value(dt, race_res.get_resistance_value(dt) + class_res.get_resistance_value(dt));
    }
  }

  return res;
}
// Calculate eq resistances.  The values returned from this function
// represent offsets - e.g., "0.2" means "0.2 more than standard", rather than
// "the value is actually 0.2".  This allows the other calculation functions
// to simply sum the offset values to get the total value.
Resistances ResistancesCalculator::calculate_equipment_resistances(CreaturePtr creature)
{
  Resistances res;
  res.set_all_resistances_to(0);

  if (creature)
  {
    Equipment& eq = creature->get_equipment();
  
    for (EquipmentWornLocation ewl = EQUIPMENT_WORN_HEAD; ewl < EQUIPMENT_WORN_LAST; ewl++)
    {
      ItemPtr item = eq.get_item(ewl);

      if (item)
      {
        Resistances item_res = item->get_resistances();

        for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
        {
          res.set_resistance_value(dt, res.get_resistance_value(dt) + item_res.get_resistance_value(dt));
        }
      }
    }
  }

  return res;
}

#ifdef UNIT_TESTS
#include "unit_tests/ResistancesCalculator_test.cpp"
#endif
