#include "DoorBreakageCalculator.hpp"

const int DoorBreakageCalculator::DEFAULT_STR_BASE = 0;
const int DoorBreakageCalculator::DEFAULT_STR_LOCK = 10;
const int DoorBreakageCalculator::STR_INCR_DIVISOR = 1;

DoorBreakageCalculator::DoorBreakageCalculator()
: material_base_strength_values({{MaterialType::MATERIAL_TYPE_WOOD, 0}, 
                                 {MaterialType::MATERIAL_TYPE_STONE, 50}, 
                                 {MaterialType::MATERIAL_TYPE_IRON, 60}, 
                                 {MaterialType::MATERIAL_TYPE_STEEL, 70}})
{
}

// Door breakage is based on the number of strength points above a certain
// threshold, which varies depending on the door's material.
int DoorBreakageCalculator::calculate_pct_chance_breakage(CreaturePtr creature, EntrancePtr entr)
{
  int chance = 0;

  if (creature && entr)
  {
    int base_str_val = get_base_strength_value(entr);
    int creature_str = creature->get_strength().get_current();

    if (creature_str > base_str_val)
    {
      int d_str = creature_str - base_str_val;
      chance += static_cast<int>(d_str / STR_INCR_DIVISOR);
    }
  }

  return chance;
}

int DoorBreakageCalculator::get_base_strength_value(EntrancePtr entr)
{
  int base_str = DEFAULT_STR_BASE;

  if (entr != nullptr)
  {
    MaterialType mt = entr->get_material_type();
    auto m_it = material_base_strength_values.find(mt);

    if (m_it != material_base_strength_values.end())
    {
      base_str = m_it->second;
    }

    LockPtr lock = entr->get_lock();

    // Locked doors are harder to kick down.
    // Not for any good reason, but for game balance and mechanic purposes.
    // Otherwise, kick kick kick kick...
    if (lock != nullptr && lock->get_locked() && !lock->get_lock_id().empty())
    {
      base_str += DEFAULT_STR_LOCK;
    }
  }

  return base_str;
}

#ifdef UNIT_TESTS
#include "unit_tests/DoorBreakageCalculator_test.cpp"
#endif