#include "StatisticsCalculators.hpp"

using namespace std;

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

    int modifier_val = get_modifier_value(creature);

    current += modifier_val;
  }

  return current;
}

int StatisticsCalculator::get_modifier_value(CreaturePtr creature) const
{
  int modifier_value = 0;

  if (creature)
  {
    const map<double, vector<pair<string, Modifier>>>& modifiers = creature->get_modifiers_ref();

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

#ifdef UNIT_TESTS
#include "unit_tests/StatisticsCalculators_test.cpp"
#endif
