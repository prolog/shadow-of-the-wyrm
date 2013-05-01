#pragma once
#include <map>
#include "EquipmentTypes.hpp"
#include "Item.hpp"
#include "ISerializable.hpp"

typedef std::map<EquipmentWornLocation, ItemPtr> EquipmentMap;

// Equipment is a class that represents all the "worn" equipment of a particular creature -
// the items that are not carried as inventory.
class Equipment : public ISerializable
{
  public:
    Equipment();
    ~Equipment();
    bool operator==(const Equipment& e) const;
    
    bool set_item(ItemPtr item, const EquipmentWornLocation location);
    ItemPtr get_item(const EquipmentWornLocation location) const;
    ItemPtr remove_item(const EquipmentWornLocation location);
    
    // Used to determine if a single item must be equipped (most slots), or if
    // multiple items are allowed (ammunition).
    bool can_equip_multiple_items(const EquipmentWornLocation location) const;
    
    bool merge(ItemPtr item);
    
    EquipmentMap get_equipment() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    void initialize();
    EquipmentMap equipment;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
