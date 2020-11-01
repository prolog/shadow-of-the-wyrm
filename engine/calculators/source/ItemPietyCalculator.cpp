#include "ItemPietyCalculator.hpp"
#include "ConsumableConstants.hpp"
#include "Consumable.hpp"

const int ItemPietyCalculator::MINIMUM_PIETY = 10;
const int ItemPietyCalculator::MINIMUM_NUTRITION_FOR_PIETY = 1000;
const int ItemPietyCalculator::BASE_DIVISOR = 10;
const int ItemPietyCalculator::CORPSE_DIVISOR = 3;
const int ItemPietyCalculator::CURRENCY_DIVISOR = 3;
const int ItemPietyCalculator::ARTIFACT_DIVISOR = 2;

// Calculate the piety granted for the sacrifice of a particular item.
// - If the item's piety is less than the minimum piety, a piety of 0
//   is returned instead.
int ItemPietyCalculator::calculate_piety(ItemPtr item)
{
  int piety = 0;
  int item_piety = 0;
  int divisor = get_base_divisor(item);
  int base_value = get_base_value(item);

  if (item)
  {
    // Since a stack of items can be sacrificed, ensure that this is properly
    // accounted for in the piety.
    item_piety = base_value;
    item_piety *= item->get_quantity();
    item_piety /= divisor;
  }

  if (item_piety > MINIMUM_PIETY)
  {
    piety = item_piety;
  }

  return piety;
}

// Get the base value of an item.  For items that are not food, this is just
// the value of the item.  But because deities enjoy cereal offerings, the
// base value for food (whether apples, food rations, corpses, etc) is the
// nutritional value.
int ItemPietyCalculator::get_base_value(ItemPtr item)
{
  int base_value = 0;

  if (item)
  {
    if (item->get_type() == ItemType::ITEM_TYPE_FOOD || item->get_type() == ItemType::ITEM_TYPE_PLANT)
    {
      ConsumablePtr consumable = std::dynamic_pointer_cast<Consumable>(item);

      if (consumable)
      {
        int nutrition = consumable->get_nutrition();

        if (nutrition >= MINIMUM_NUTRITION_FOR_PIETY || consumable->get_effect_type() != EffectType::EFFECT_TYPE_NULL)
        {
          base_value = nutrition;
        }
      }
    }
    else
    {
      base_value = item->get_value();
    }
  }

  return base_value;
}

// Deities appreciate corpses more than anything else, so the divisor for
// corpses is much lower than for any other item.
int ItemPietyCalculator::get_base_divisor(ItemPtr item)
{
  int divisor = BASE_DIVISOR;

  if (item)
  {
    if (item->has_additional_property(ConsumableConstants::CORPSE_RACE_ID))
    {
      divisor = CORPSE_DIVISOR;
    }

    if (item->get_type() == ItemType::ITEM_TYPE_CURRENCY)
    {
      divisor = CURRENCY_DIVISOR;
    }

    if (item->get_artifact())
    {
      divisor /= ARTIFACT_DIVISOR;
    }
  }

  return divisor;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemPietyCalculator_test.cpp"
#endif