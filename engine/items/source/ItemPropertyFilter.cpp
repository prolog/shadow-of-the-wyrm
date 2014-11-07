#include "ItemPropertyFilter.hpp"

using namespace std;

ItemPropertyFilter::ItemPropertyFilter(const pair<string, string>& prop_pair)
: property(prop_pair)
{
}

// The item passes the filter when the item:
// - Is non-null
// - Has the property, and the filter's value is empty, or
// - Has the property, and the filter's value is not empty, and the value matches
//   the filter value.
bool ItemPropertyFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    if (property.second.empty())
    {
      passes = item->has_additional_property(property.first);
    }
    else
    {
      passes = (item->get_additional_property(property.first) == property.second);
    }
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemPropertyFilter_test.cpp"
#endif

