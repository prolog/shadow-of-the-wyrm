#pragma once
#include <list>
#include <vector>
#include "IItemFilter.hpp"
#include "EquipmentTypes.hpp"

class ItemFilterFactory
{
  public:
    // Uses the constants found in LuaItemFilter.hpp
    static std::list<IItemFilterPtr> create_script_filter(const int script_constant);

    static std::list<IItemFilterPtr> create_empty_filter();
    static std::list<IItemFilterPtr> create_equipment_filter(const std::list<EquipmentWornLocation>& worn_list);
    static std::list<IItemFilterPtr> create_item_type_filter(const ItemType item_type);
    static std::list<IItemFilterPtr> create_item_type_filter(const std::list<ItemType>& item_type_list);
    static std::list<IItemFilterPtr> create_item_type_filter(const int display_symbol);
    static std::list<IItemFilterPtr> create_item_property_type_filter(const std::vector<std::pair<std::string, std::string>>& property_value_pairs);
    static std::list<IItemFilterPtr> create_material_type_filter(const MaterialType material);
    static std::list<IItemFilterPtr> create_readable_filter();
    static std::list<IItemFilterPtr> create_edible_filter();
    static std::list<IItemFilterPtr> create_hands_required_filter(const int hands_available);
    
    static IItemFilterPtr create_equipment_worn_location_filter(const EquipmentWornLocation& ewl);

};
