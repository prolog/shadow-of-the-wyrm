#include <algorithm>
#include "ItemTypeFilter.hpp"

using namespace std;

ItemTypeFilter::ItemTypeFilter(const ItemType it)
: item_types({it})
{
}

ItemTypeFilter::ItemTypeFilter(const list<ItemType>& new_item_types)
: item_types(new_item_types)
{
}

bool ItemTypeFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    ItemType i_type = item->get_type();
    passes = (std::find(item_types.begin(), item_types.end(), i_type) != item_types.end());
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemTypeFilter_test.cpp"
#endif
