#pragma once
#include "Creature.hpp"
#include "Item.hpp"

class ItemManager
{
  public:
    ItemManager();
    ~ItemManager();

    // Create a new item from a given item.  This is used to make copies of the
    // template items, so that, say, fifty distinct broadswords can be created.
    ItemPtr create_item(const ItemMap& items, const std::string& item_id);

    // JCD FIXME: This will need to be updated to have functionality that
    // adds/removes the item from its tile, when applicable.
    bool pick_up(CreaturePtr creature, ItemPtr item);
    bool drop(CreaturePtr creature, ItemPtr item);
    bool equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation location);
    bool equip(CreaturePtr creature, ItemPtr item);
    ItemPtr remove(CreaturePtr creature, const EquipmentWornLocation location);
};
