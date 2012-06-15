#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Item.hpp"

class ItemManager : public IActionManager
{
  public:
    ItemManager();
    ~ItemManager();

    // Create a new item from a given item.  This is used to make copies of the
    // template items, so that, say, fifty distinct broadswords can be created.
    ItemPtr create_item(const ItemMap& items, const std::string& item_id);
    
    static ItemPtr create_item(const std::string& item_id); // This version assumes that we use the collection on the Game singleton.
    static void create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_bound, Inventory& inv, const std::string& item_id);

    // JCD FIXME: This will need to be updated to have functionality that
    // adds/removes the item from its tile, when applicable.
    bool pick_up(CreaturePtr creature, ItemPtr item);
    bool drop(CreaturePtr creature, ItemPtr item);
    bool equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation location);
    bool equip(CreaturePtr creature, ItemPtr item);
    ItemPtr remove(CreaturePtr creature, const EquipmentWornLocation location);
    
  protected:
    uint get_current_action_cost() const;

};
