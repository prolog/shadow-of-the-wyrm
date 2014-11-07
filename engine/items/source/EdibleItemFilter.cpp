#include "EdibleItemFilter.hpp"

// Check to see if the item is edible
bool EdibleItemFilter::passes_filter(ItemPtr item) const
{
  if (item)
  {
    ItemType type = item->get_type();
    
    if (type == ITEM_TYPE_FOOD || type == ITEM_TYPE_PLANT)
    {
      return true;
    }
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/EdibleItemFilter_test.cpp"
#endif
