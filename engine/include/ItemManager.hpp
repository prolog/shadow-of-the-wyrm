#pragma once
#include "Creature.hpp"
#include "Item.hpp"

class ItemManager
{
  public:
    ItemManager();
    ~ItemManager();

    // JCD FIXME: This will need to be updated to have functionality that
    // adds/removes the item from its tile, when applicable.
    bool pick_up(CreaturePtr creature, ItemPtr item);
    bool drop(CreaturePtr creature, ItemPtr item);
    bool equip(CreaturePtr creature, ItemPtr item);
};
