#include "DisplayItemTypeFactory.hpp"
#include "EdibleItemFilter.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemPropertyFilter.hpp"
#include "ItemTypeFilter.hpp"
#include "NullItemFilter.hpp"
#include "ReadableItemFilter.hpp"
#include "SquishyEquipWornLocationFilter.hpp"

using namespace std;

// Create a 1-item list that always passes - used for things like pickup,
// drop, etc., where the initial filter is always empty.
list<IItemFilterPtr> ItemFilterFactory::create_empty_filter()
{
  list<IItemFilterPtr> null_filter_list;

  IItemFilterPtr null_filter = std::make_shared<NullFilter>();
  null_filter_list.push_back(null_filter);

  return null_filter_list;
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

  for (const ItemType it : item_type_list)
  {
    IItemFilterPtr display_filter = std::make_shared<ItemTypeFilter>(it);
    it_filter.push_back(display_filter);
  }
  
  return it_filter;
}

// Create an item type filter from a user-entered keyboard value.
list<IItemFilterPtr> ItemFilterFactory::create_item_type_filter(const int display_symbol)
{
  list<IItemFilterPtr> it_filter;
  list<ItemType> it_list;

  DisplayItemTypePtr dit = DisplayItemTypeFactory::create(display_symbol);

  if (dit != nullptr)
  {
    it_list.push_back(dit->get_item_type());
  }

  it_filter = create_item_type_filter(it_list);
  DisplayItemTypeFactory;
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
