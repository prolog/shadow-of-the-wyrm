#include "StatisticsCalculators.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "Wearable.hpp"

using namespace std;

const float SpeedCalculator::BURDENED_SPEED_MULTIPLIER = 1.5f;
const float SpeedCalculator::STRAINED_SPEED_MULTIPLIER = 2.0f;
const float SpeedCalculator::OVERBURDENED_SPEED_MULTIPLIER = 3.0f;

// Calculate the current value of a statistic.
//
// Currently, this only considers values as part of modifiers on
// the creature.
int StatisticsCalculator::calculate_current(CreaturePtr creature) const
{
  int current = 0;

  if (creature != nullptr)
  {
    current = get_base_statistic_value(creature);
    int value_multiplier = get_value_multiplier();

    int equipment_val = get_equipment_value(creature);
    int modifier_val = get_modifier_value(creature);
    float burden_multiplier = get_burden_multiplier(creature);
    current += (equipment_val * value_multiplier);
    current += (modifier_val * value_multiplier);
    current = static_cast<int>(current * burden_multiplier);

    current = std::max(current, 1);
  }

  return current;
}

// JCD FIXME Eventually I'll want to implement equipment with stats
// bonuses.  When that happens, implement this.
int StatisticsCalculator::get_equipment_value(CreaturePtr /*creature*/) const
{
  return 0;
}

float StatisticsCalculator::get_burden_multiplier(CreaturePtr /*creature*/) const
{
  return 1.0f;
}

// Most statistics want positive values, and should have a value multiplier
// of 1.  Speed's a special case, lower being better, and this should have
// a value multiplier of -1.
int StatisticsCalculator::get_value_multiplier() const
{
  return 1;
}

int StatisticsCalculator::get_modifier_value(CreaturePtr creature) const
{
  int modifier_value = 0;

  if (creature)
  {
    const map<double, vector<pair<string, Modifier>>> modifiers = creature->get_active_modifiers();

    for (const auto& mod_pair : modifiers)
    {
      for (const auto& current_mod_pair : mod_pair.second)
      {
        modifier_value += get_modifier_statistic_value(current_mod_pair.second);
      }
    }
  }

  return modifier_value;
}

// Strength
int StrengthCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_strength().get_base();
  }

  return base_val;
}

int StrengthCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_strength_modifier();
}

// Dexterity
int DexterityCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_dexterity().get_base();
  }

  return base_val;
}

int DexterityCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_dexterity_modifier();
}

// Agility
int AgilityCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_agility().get_base();
  }

  return base_val;
}

int AgilityCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_agility_modifier();
}


// Health
int HealthCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_health().get_base();
  }

  return base_val;
}

int HealthCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_health_modifier();
}

// Intelligence
int IntelligenceCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_intelligence().get_base();
  }
  
  return base_val;
}

int IntelligenceCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_intelligence_modifier();
}

// Willpower
int WillpowerCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_willpower().get_base();
  }

  return base_val;
}

int WillpowerCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_willpower_modifier();
}

// Charisma
int CharismaCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_charisma().get_base();
  }

  return base_val;
}

int CharismaCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_charisma_modifier();
}

int SpeedCalculator::get_base_statistic_value(CreaturePtr creature) const
{
  int base_val = 0;

  if (creature != nullptr)
  {
    base_val = creature->get_speed().get_base();
  }

  return base_val;
}

int SpeedCalculator::get_modifier_statistic_value(const Modifier& m) const
{
  return m.get_speed_modifier();
}

int SpeedCalculator::get_value_multiplier() const
{
  return -1;
}

int SpeedCalculator::get_equipment_value(CreaturePtr creature) const
{
  Equipment& eq = creature->get_equipment();
  int eq_speed_bonus = 0;

  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    ItemPtr item = eq.get_item(static_cast<EquipmentWornLocation>(e));
    WearablePtr item_w = std::dynamic_pointer_cast<Wearable>(item);

    if (item_w != nullptr)
    {
      eq_speed_bonus += item_w->get_speed_bonus();
    }
  }

  return eq_speed_bonus;
}

float SpeedCalculator::get_burden_multiplier(CreaturePtr creature) const
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    Weight total_weight = creature->get_weight_carried();
    uint weight_in_oz = total_weight.get_weight();

    CarryingCapacityCalculator ccc;

    if (weight_in_oz >= ccc.calculate_overburdened_weight(creature))
    {
      mult = OVERBURDENED_SPEED_MULTIPLIER;
    }
    else if (weight_in_oz >= ccc.calculate_strained_weight(creature))
    {
      mult = STRAINED_SPEED_MULTIPLIER;
    }
    else if (weight_in_oz >= ccc.calculate_burdened_weight(creature))
    {
      mult = BURDENED_SPEED_MULTIPLIER;
    }
  }

  return mult;
}


#ifdef UNIT_TESTS
#include "unit_tests/StatisticsCalculators_test.cpp"
#endif
