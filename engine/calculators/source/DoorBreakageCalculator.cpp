#include "DoorBreakageCalculator.hpp"

const int DoorBreakageCalculator::DEFAULT_STR_BASE = 10;
const int DoorBreakageCalculator::STR_INCR_DIVISOR = 3;

DoorBreakageCalculator::DoorBreakageCalculator()
: material_base_strength_values({{MaterialType::MATERIAL_TYPE_WOOD, 10}, 
                                 {MaterialType::MATERIAL_TYPE_STONE, 50}, 
                                 {MaterialType::MATERIAL_TYPE_IRON, 60}, 
                                 {MaterialType::MATERIAL_TYPE_STEEL, 70}})
{
}

// Door breakage is based on the number of strength points above a certain
// threshold, which varies depending on the door's material.
int DoorBreakageCalculator::calculate_pct_chance_breakage(CreaturePtr creature, DoorPtr door)
{
  int chance = 0;

  if (creature && door)
  {
    int base_str_val = get_base_strength_value(door->get_material_type());
    int creature_str = creature->get_strength().get_current();

    if (creature_str > base_str_val)
    {
      int d_str = creature_str - base_str_val;
      chance += static_cast<int>(d_str / STR_INCR_DIVISOR);
    }
  }

  return chance;
}

int DoorBreakageCalculator::get_base_strength_value(const MaterialType mt)
{
  int base_str = DEFAULT_STR_BASE;
  auto m_it = material_base_strength_values.find(mt);

  if (m_it != material_base_strength_values.end())
  {
    base_str = m_it->second;
  }

  return base_str;
}

#ifdef UNIT_TESTS
#include "unit_tests/DoorBreakageCalculator_test.cpp"
#endif