#pragma once
#include <list>
#include "IItemDisplayFilter.hpp"
#include "EquipmentTypes.hpp"

class ItemDisplayFilterFactory
{
  public:
    static std::list<IItemDisplayFilterPtr> create_empty_filter();
    static std::list<IItemDisplayFilterPtr> create_equipment_filter(const std::list<EquipmentWornLocation>& worn_list);
    static std::list<IItemDisplayFilterPtr> create_item_type_filter(const ItemType item_type);
    static std::list<IItemDisplayFilterPtr> create_item_type_filter(const std::list<ItemType>& item_type_list);
    
    static IItemDisplayFilterPtr create_equipment_worn_location_filter(const EquipmentWornLocation& ewl);

};
