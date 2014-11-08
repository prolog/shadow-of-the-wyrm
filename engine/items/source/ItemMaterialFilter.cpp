#include "ItemMaterialFilter.hpp"

using namespace std;

ItemMaterialFilter::ItemMaterialFilter(const MaterialType new_material)
: material(new_material)
{
}

// The item passes the filter when the item:
// - Is non-null
// - Matches the material
bool ItemMaterialFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    passes = (material == item->get_material_type());
  }

  return passes;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemMaterialFilter_test.cpp"
#endif

