#include "ItemPietyCalculator.hpp"

const int ItemPietyCalculator::MINIMUM_PIETY = 100;

// Calculate the piety granted for the sacrifice of a particular item.
// - If the item's piety is less than the minimum piety, a piety of 0
//   is returned instead.
int ItemPietyCalculator::calculate_piety(ItemPtr item)
{
  int piety = 0;
  int item_piety = 0;

  if (item)
  {
    // Since a stack of items can be sacrificed, ensure that this is properly
    // accounted for in the piety.
    item_piety *= item->get_quantity();
  }

  if (item_piety > MINIMUM_PIETY)
  {
    piety = item_piety;
  }

  return piety;
}

// TODO: Unit tests!