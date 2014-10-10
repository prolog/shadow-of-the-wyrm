#include "ItemPietyCalculator.hpp"
#include "ConsumableConstants.hpp"

const int ItemPietyCalculator::MINIMUM_PIETY = 50;
const int ItemPietyCalculator::BASE_DIVISOR = 10;

// Calculate the piety granted for the sacrifice of a particular item.
// - If the item's piety is less than the minimum piety, a piety of 0
//   is returned instead.
int ItemPietyCalculator::calculate_piety(ItemPtr item)
{
  int piety = 0;
  int item_piety = 0;
  int divisor = BASE_DIVISOR;

  if (item)
  {
    // Since a stack of items can be sacrificed, ensure that this is properly
    // accounted for in the piety.
    item_piety *= item->get_quantity();
  }

  if (item->has_additional_property(ConsumableConstants::CORPSE_RACE_ID))
  {
    // ...
  }

  if (item_piety > MINIMUM_PIETY)
  {
    piety = item_piety;
  }

  return piety;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemPietyCalculator_test.cpp"
#endif