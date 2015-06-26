#include "CarryingCapacityCalculator.hpp"

CarryingCapacityCalculator::CarryingCapacityCalculator()
: CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER(10),
  carrying_capacity_multipliers({{CreatureSize::CREATURE_SIZE_TINY, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_SMALL, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_MEDIUM, 1.0f},
                                 {CreatureSize::CREATURE_SIZE_LARGE, 1.5f},
                                 {CreatureSize::CREATURE_SIZE_BEHEMOTH, 2.0f}})
{
  static_assert(CreatureSize::CREATURE_SIZE_LAST == CreatureSize(6), "Unexpected CREATURE_SIZE_LAST!");
}

// A creature can carry a total number of items equal to:
// 10 * its dexterity
//    * the carrying capacity multiplier based on its size
uint CarryingCapacityCalculator::calculate_carrying_capacity_total_items(CreaturePtr creature)
{
  uint capacity = 0;

  if (creature != nullptr)
  {
    uint base = creature->get_dexterity().get_current();
    float size_multiplier = carrying_capacity_multipliers.find(creature->get_size())->second;

    capacity = static_cast<uint>(base * CARRYING_CAPACITY_TOTAL_ITEMS_MULTIPLIER * size_multiplier);
  }

  return capacity;
}

#ifdef UNIT_TESTS
#include "unit_tests/CarryingCapacityCalculator_test.cpp"
#endif

