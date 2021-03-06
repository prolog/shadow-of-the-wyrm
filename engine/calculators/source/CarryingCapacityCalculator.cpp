#include "CarryingCapacityCalculator.hpp"

CarryingCapacityCalculator::CarryingCapacityCalculator()
: CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER(10),
  carrying_capacity_multipliers({{CreatureSize::CREATURE_SIZE_TINY, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_SMALL, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_MEDIUM, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_LARGE, 1.5f},
                                 {CreatureSize::CREATURE_SIZE_HUGE, 2.0f},
                                 {CreatureSize::CREATURE_SIZE_BEHEMOTH, 2.0f}})
{
  static_assert(CreatureSize::CREATURE_SIZE_LAST == CreatureSize(6), "Unexpected CREATURE_SIZE_LAST!");
}

// A creature can carry a total number of items equal to:
// 10 * its dexterity
//    * the carrying capacity multiplier based on its size
uint CarryingCapacityCalculator::calculate_carrying_capacity_total_items(CreaturePtr creature) const
{
  uint capacity = 0;

  if (creature != nullptr)
  {
    uint base = creature->get_dexterity().get_current();
    auto sm_it = carrying_capacity_multipliers.find(creature->get_size());
    float size_multiplier = 1.0f;
    float skill_multiplier = calculate_total_items_skill_multiplier(creature);

    if (sm_it != carrying_capacity_multipliers.end())
    {
      size_multiplier = carrying_capacity_multipliers.find(creature->get_size())->second;
    }

    capacity = static_cast<uint>(base 
                               * CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER
                               * size_multiplier 
                               * skill_multiplier);
  }

  return capacity;
}

// Calculate the weight at which a creature becomes burdened (80% speed)
//
// A creature can carry 10 times their strength in pounds before becoming burdened.
uint CarryingCapacityCalculator::calculate_burdened_weight(CreaturePtr creature) const
{
  uint burdened_weight = 0;

  if (creature != nullptr)
  {
    Statistic str = creature->get_strength();
    burdened_weight = 10 * str.get_current();
    burdened_weight = static_cast<uint>(burdened_weight * calculate_weight_skill_multiplier(creature));
    burdened_weight *= 16; // convert from lbs to oz
  }

  return burdened_weight;
}

// Calculate the weight at which a creature becomes strained (40% speed)
//
// A creature can carry 15 times their strength in pounds before becoming strained.
uint CarryingCapacityCalculator::calculate_strained_weight(CreaturePtr creature) const
{
  uint strained_weight = 0;

  if (creature != nullptr)
  {
    Statistic str = creature->get_strength();
    strained_weight = 15 * str.get_current();
    strained_weight = static_cast<uint>(strained_weight * calculate_weight_skill_multiplier(creature));
    strained_weight *= 16; // convert from lbs to oz
  }

  return strained_weight;
}

// Calculate the weight at which a creature becomes overburdened (cannot move)
//
// A creature can carry 20 times their strength in pounds before becoming overburdened.
uint CarryingCapacityCalculator::calculate_overburdened_weight(CreaturePtr creature) const
{
  uint overburdened_weight = 0;

  if (creature != nullptr)
  {
    Statistic str = creature->get_strength();
    overburdened_weight = 20 * str.get_current();
    overburdened_weight = static_cast<uint>(overburdened_weight * calculate_weight_skill_multiplier(creature));
    overburdened_weight *= 16; // convert from lbs to oz
  }

  return overburdened_weight;
}

// The skill multiplier is 1.0 + 0.01 for every point of carrying.
float CarryingCapacityCalculator::calculate_total_items_skill_multiplier(CreaturePtr creature) const
{
  float skill_mult = 1.0f;

  if (creature != nullptr)
  {
    skill_mult += (creature->get_skills().get_value(SkillType::SKILL_GENERAL_CARRYING) * 0.01f);
  }

  return skill_mult;
}

// The weight multiplier (for total weight until burdened, etc) is 1.0
// + 0.02 for every point of carrying.
float CarryingCapacityCalculator::calculate_weight_skill_multiplier(CreaturePtr creature) const
{
  float skill_mult = 1.0f;

  if (creature != nullptr)
  {
    skill_mult += (creature->get_skills().get_value(SkillType::SKILL_GENERAL_CARRYING) * 0.02f);
  }

  return skill_mult;
}

#ifdef UNIT_TESTS
#include "unit_tests/CarryingCapacityCalculator_test.cpp"
#endif

