#include "CreatureSpeedCalculator.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "Wearable.hpp"

const float CreatureSpeedCalculator::BURDENED_SPEED_MULTIPLIER = 1.20f;
const float CreatureSpeedCalculator::STRAINED_SPEED_MULTIPLIER = 1.5f;

int CreatureSpeedCalculator::calculate(CreaturePtr creature) const
{
  int calc_speed = 0;

  if (creature != nullptr)
  {
    Statistic speed = creature->get_speed();
    calc_speed = speed.get_base();

    calc_speed -= get_equipment_bonus(creature);
    float multiplier = get_multiplier(creature);

    calc_speed = static_cast<int>(calc_speed * multiplier);
  }

  return calc_speed;
}

int CreatureSpeedCalculator::get_equipment_bonus(CreaturePtr creature) const
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

float CreatureSpeedCalculator::get_multiplier(CreaturePtr creature) const
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    Weight total_weight = creature->get_weight_carried();
    uint weight_in_oz = total_weight.get_weight();

    CarryingCapacityCalculator ccc;

    if (weight_in_oz >= ccc.calculate_strained_weight(creature))
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
#include "unit_tests/CreatureSpeedCalculator_test.cpp"
#endif

