#include "Resistances.hpp"
#include "ResistancesCalculator.hpp"

using namespace std;

Resistances ResistancesCalculator::default_resistances()
{
  Resistances resists;
  
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    double value = DEFAULT_RESISTANCE_VALUE;
    resists.set_resistance_value(dt, value);
  }
  
  return resists;
}

Resistances ResistancesCalculator::calculate_resistances(CreaturePtr creature, RacePtr race, ClassPtr cur_class)
{
  Resistances resists_calculated;
  Resistances resists_eq = calculate_equipment_resistances(creature);

  double noneq_val  = 0.0;
  double eq_val     = 0.0;
  double total_val  = 0.0;

  // Combines race and class resistances, along with the creature's intrinsic
  // values (gained along the way).
  Resistances resists_noneq = calculate_non_equipment_resistances(creature, race, cur_class);

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);

    // A positive value (e.g., 0.25) means increased resistance.
    // Since the resistance is a multiplier, to increase resistance,
    // we subtract the value from 1 to get a value less than 1,
    // which will in turn reduce damage.
    noneq_val = resists_noneq.get_resistance_value(dt);
    eq_val    = resists_eq.get_resistance_value(dt);
    total_val = 1 - (eq_val + noneq_val);
      
    resists_calculated.set_resistance_value(dt, total_val);
  }

  return resists_calculated;
}

// Calculate the creature's combined race, class, and intrinsic resistances.
Resistances ResistancesCalculator::calculate_non_equipment_resistances(CreaturePtr creature, RacePtr race, ClassPtr cur_class)
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

    // Spells may contain resistance modifiers.
    Resistances modifier_res = calculate_modifier_resistances(creature);

    // Any intrinsics?
    Resistances intr_res = creature->get_intrinsic_resistances();

    for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
    {
      DamageType dt = static_cast<DamageType>(d);

      double non_eq_value = race_res.get_resistance_value(dt)
                          + class_res.get_resistance_value(dt)
                          + modifier_res.get_resistance_value(dt)
                          + intr_res.get_resistance_value(dt);

      res.set_resistance_value(dt, non_eq_value);
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
  
    for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
    {
      EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);

      ItemPtr item = eq.get_item(ewl);

      if (item)
      {
        Resistances item_res = item->get_resistances();

        for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
        {
          DamageType dt = static_cast<DamageType>(d);
          res.set_resistance_value(dt, res.get_resistance_value(dt) + item_res.get_resistance_value(dt));
        }
      }
    }
  }

  return res;
}

Resistances ResistancesCalculator::calculate_modifier_resistances(CreaturePtr creature)
{
  Resistances res;
  res.set_all_resistances_to(0);

  if (creature != nullptr)
  {
    const map<double, vector<pair<string, Modifier>>>& modifiers = creature->get_modifiers_ref();

    for (const auto& mod_pair : modifiers)
    {
      for (const auto& current_mod_pair : mod_pair.second)
      {
        res.add(current_mod_pair.second.get_resistances());
      }
    }
  }

  return res;
}

#ifdef UNIT_TESTS
#include "unit_tests/ResistancesCalculator_test.cpp"
#endif
