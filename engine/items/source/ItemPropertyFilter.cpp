#include "ItemPropertyFilter.hpp"

using namespace std;

ItemPropertyFilter::ItemPropertyFilter(const pair<string, string>& prop_pair)
: property(prop_pair)
{
}

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
