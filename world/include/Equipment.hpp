#pragma once
#include <map>
#include "EquipmentTypes.hpp"
#include "Item.hpp"

typedef std::map<EquipmentWornLocation, ItemPtr> EquipmentMap;

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
    
    // Used to determine if a single item must be equipped (most slots), or if
    // multiple items are allowed (ammunition).
    bool can_equip_multiple_items(const EquipmentWornLocation location) const;
    
    bool merge(ItemPtr item);
    
    EquipmentMap get_equipment() const;

  protected:
    void initialize();
    EquipmentMap equipment;
};
