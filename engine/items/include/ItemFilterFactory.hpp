#pragma once
#include <list>
#include "IItemFilter.hpp"
#include "EquipmentTypes.hpp"

class ItemFilterFactory
{
  public:
    static std::list<IItemFilterPtr> create_empty_filter();
    static std::list<IItemFilterPtr> create_equipment_filter(const std::list<EquipmentWornLocation>& worn_list);
    static std::list<IItemFilterPtr> create_item_type_filter(const ItemType item_type);
    static std::list<IItemFilterPtr> create_item_type_filter(const std::list<ItemType>& item_type_list);
    static std::list<IItemFilterPtr> create_readable_filter();
    
    static IItemFilterPtr create_equipment_worn_location_filter(const EquipmentWornLocation& ewl);

};
