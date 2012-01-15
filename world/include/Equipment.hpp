#pragma once
#include <map>
#include "EquipmentTypes.hpp"
#include "Item.hpp"

// Equipment is a class that represents all the "worn" equipment of a particular creature -
// the items that are not carried as inventory.
class Equipment
{
  public:
    Equipment();
    ~Equipment();
    
    bool set_item(ItemPtr item, const EquipmentWornLocation location);
    ItemPtr get_item(const EquipmentWornLocation location) const;
    ItemPtr remove_item(const EquipmentWornLocation location);

  protected:
    void initialize();
    std::map<EquipmentWornLocation, ItemPtr> equipment;
};
