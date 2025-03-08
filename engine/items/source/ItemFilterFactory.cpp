#include "ArtifactItemFilter.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "EdibleItemFilter.hpp"
#include "HandsRequiredItemFilter.hpp"
#include "ItemBaseIdFilter.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemMaterialFilter.hpp"
#include "ItemPropertyFilter.hpp"
#include "ItemTypeFilter.hpp"
#include "ItemUnpaidFilter.hpp"
#include "LuaItemFilter.hpp"
#include "NullItemFilter.hpp"
#include "ReadableItemFilter.hpp"
#include "SquishyEquipWornLocationFilter.hpp"
#include "UnidentifiedItemFilter.hpp"

using namespace std;

// Create a filter based on a constant (values defined in 
// LuaItemFilter.hpp) passed in from a Lua script.
list<IItemFilterPtr> ItemFilterFactory::create_script_filter(const int script_constant)
{
  list<IItemFilterPtr> filters;
  IItemFilterPtr filter;

  switch(script_constant)
  {
    case CITEM_FILTER_UNIDENTIFIED:
      filter = std::make_shared<UnidentifiedItemFilter>();
      break;
    case CITEM_FILTER_ARTIFACT:
      filter = std::make_shared<ArtifactItemFilter>();
      break;
    default:
      filter = std::make_shared<NullItemFilter>();
      break;
  }

  filters.push_back(filter);
  return filters;
}

// Create a 1-item list that always passes - used for things like pickup,
// drop, etc., where the initial filter is always empty.
list<IItemFilterPtr> ItemFilterFactory::create_empty_filter()
{
  list<IItemFilterPtr> null_filter_list;

  IItemFilterPtr null_filter = std::make_shared<NullItemFilter>();
  null_filter_list.push_back(null_filter);

  return null_filter_list;
}

list<IItemFilterPtr> ItemFilterFactory::create_unpaid_filter()
{
  list<IItemFilterPtr> unpaid_filter_list;

  IItemFilterPtr unpaid = std::make_shared<ItemUnpaidFilter>();
  unpaid_filter_list.push_back(unpaid);

  return unpaid_filter_list;
}

// Create a list of filters for the passed-in worn locations.
list<IItemFilterPtr> ItemFilterFactory::create_equipment_filter(const std::list<EquipmentWornLocation>& eq_loc_list)
{
  list<IItemFilterPtr> ewl_list;
  
  for (const EquipmentWornLocation& ewl : eq_loc_list)
  {
    IItemFilterPtr eq_filter = create_equipment_worn_location_filter(ewl);
    ewl_list.push_back(eq_filter);
  }
  
  return ewl_list;
}

// Create a filter by equipment worn location
IItemFilterPtr ItemFilterFactory::create_equipment_worn_location_filter(const EquipmentWornLocation& ewl)
{
  IItemFilterPtr eq_filter = std::make_shared<SquishyEquipWornLocationFilter>(ewl);
  return eq_filter;
}

// Create a filter by item type.
list<IItemFilterPtr> ItemFilterFactory::create_item_type_filter(const ItemType item_type)
{
  list<IItemFilterPtr> it_filter;
  list<ItemType> it_list;
  it_list.push_back(item_type);
  
  return create_item_type_filter(it_list);
}

list<IItemFilterPtr> ItemFilterFactory::create_item_type_filter(const std::list<ItemType>& item_type_list)
{
  list<IItemFilterPtr> it_filter;

  IItemFilterPtr display_filter = std::make_shared<ItemTypeFilter>(item_type_list);
  it_filter.push_back(display_filter);
  
  return it_filter;
}

// Create an item type (or unpaid) filter from a user-entered keyboard value.
list<IItemFilterPtr> ItemFilterFactory::create_item_type_filter(const int display_symbol)
{
  list<IItemFilterPtr> it_filter;
  list<ItemType> it_list;

  vector<DisplayItemTypePtr> dit_v = DisplayItemTypeFactory::create(display_symbol);

  for (DisplayItemTypePtr dit : dit_v)
  {
    if (dit != nullptr)
    {
      it_list.push_back(dit->get_item_type());
    }
  }

  it_filter = create_item_type_filter(it_list);
  return it_filter;
}

list<IItemFilterPtr> ItemFilterFactory::create_item_property_type_filter(const vector<pair<string, string>>& property_list)
{
  list<IItemFilterPtr> it_filter;

  for (pair<string, string> prop : property_list)
  {
    IItemFilterPtr property_filter = std::make_shared<ItemPropertyFilter>(prop);
    it_filter.push_back(property_filter);
  }

  return it_filter;
}

// Create a filter containing all readable items (books and scrolls)
list<IItemFilterPtr> ItemFilterFactory::create_readable_filter()
{
  list<IItemFilterPtr> it_filter;
  
  IItemFilterPtr readable_filter = std::make_shared<ReadableItemFilter>();
  it_filter.push_back(readable_filter);
  
  return it_filter;
}

// Create a filter containing all edible items (food and plants, but not
// potions)
list<IItemFilterPtr> ItemFilterFactory::create_edible_filter()
{
  list<IItemFilterPtr> it_filter;
  
  IItemFilterPtr readable_filter = std::make_shared<EdibleItemFilter>();
  it_filter.push_back(readable_filter);
  
  return it_filter;
}

list<IItemFilterPtr> ItemFilterFactory::create_hands_required_filter(const EquipmentWornLocation ewl, const int hands_available)
{
  list<IItemFilterPtr> it_filter;

  IItemFilterPtr hands_req_filter = std::make_shared<HandsRequiredItemFilter>(ewl, hands_available);
  it_filter.push_back(hands_req_filter);

  return it_filter;
}

// Create a filter by material type.
list<IItemFilterPtr> ItemFilterFactory::create_material_type_filter(const std::vector<MaterialType>& material)
{
  list<IItemFilterPtr> material_filters;

  IItemFilterPtr material_filter = std::make_shared<ItemMaterialFilter>(material);
  material_filters.push_back(material_filter);

  return material_filters;
}

list<IItemFilterPtr> ItemFilterFactory::create_item_base_id_filter(const string& item_base_id)
{
  list<IItemFilterPtr> base_id_filters;
  IItemFilterPtr base_id_filter = std::make_shared<ItemBaseIdFilter>(item_base_id);
  base_id_filters.push_back(base_id_filter);

  return base_id_filters;
}