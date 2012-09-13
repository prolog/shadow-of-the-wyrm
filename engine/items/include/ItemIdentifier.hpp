#pragma once
#include <string>
#include <vector>
#include "Creature.hpp"
#include "Item.hpp"
#include "IItemDisplayFilter.hpp"

// A class for working with logic based around an item's "identified" status.
class ItemIdentifier
{
  public:
    // Set the creature's entire possessions (equipment and inventory) identified.  Filter as necessary.
    void set_possessions_identified(CreaturePtr creature, const std::list<IItemDisplayFilterPtr> * const filter_v = NULL);

    // Set the creature's equipment identified.
    void set_equipment_identified(CreaturePtr creature, const std::list<IItemDisplayFilterPtr> * const filter_v = NULL);
    
    // Set the creature's inventory identified.
    void set_inventory_identified(CreaturePtr creature, const std::list<IItemDisplayFilterPtr> * const filter_v = NULL);
    
    // Identify all possessions of a particular type.
    void set_possessions_identified_by_type(CreaturePtr creature, const ItemType item_type);
    
    // Functions for querying or modifying a particular item's
    // identification status.
    void set_item_identified(const std::string& base_item_id, const bool is_identified) const;
    bool get_item_identified(const std::string& base_item_id) const;

    // Get the appropriate description (identified or unidentified) for
    // the items whose base item identified is base_item_id.
    std::string get_appropriate_description_sid(const std::string& base_item_id) const;
    std::string get_appropriate_usage_description_sid(const std::string& base_item_id) const;
    
  protected:
    ItemPtr get_base_item(const std::string& base_item_id) const;
};
