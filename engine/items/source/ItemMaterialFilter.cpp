#include <algorithm>
#include "ItemMaterialFilter.hpp"

using namespace std;

ItemMaterialFilter::ItemMaterialFilter(const vector<MaterialType>& new_materials)
: materials(new_materials)
{
}

// The item passes the filter when the item:
// - Is non-null
// - Matches the material
bool ItemMaterialFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item && !materials.empty())
  {
    passes = std::find(materials.begin(), materials.end(), item->get_material_type()) != materials.end();
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemMaterialFilter_test.cpp"
#endif

