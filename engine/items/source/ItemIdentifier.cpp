#include <sstream>
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemStatusTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Identify all the possessions, both equipment and inventory, of a creature.
void ItemIdentifier::set_possessions_identified(CreaturePtr creature, const list<IItemFilterPtr> * const filter_v)
{
  if (creature)
  {
    set_equipment_identified(creature, filter_v);
    set_inventory_identified(creature, filter_v);
  }
}

// Identify items in the equipment based on the filter provided.  If no filter is provided,
// then identify everything.
void ItemIdentifier::set_equipment_identified(CreaturePtr creature, const list<IItemFilterPtr> * const filter_v)
{
  if (creature)
  {
    EquipmentMap eq = creature->get_equipment().get_equipment();
        
    for (const EquipmentMap::value_type& eq_pair : eq)
    {
      bool passes_filter = (!filter_v);
      
      ItemPtr item = eq_pair.second;

      if (filter_v && item)
      {
        const list<IItemFilterPtr> filters = *filter_v;
        for (IItemFilterPtr filter : filters)
        {
          passes_filter = filter->passes_filter(item);
          
          if (!passes_filter)
          {
            break;
          }
        }
      }
      
      // This is an item to be identified (it passes all the filters), so identify it.
      if (passes_filter && item) 
      {
        set_item_identified(item, item->get_base_id(), true);
      }
    }
  }
}

// Identify items in the inventory based on the filter provided.  If no filter is provided,
// then identify everything.
void ItemIdentifier::set_inventory_identified(CreaturePtr creature, const list<IItemFilterPtr> * const filter_v)
{
  if (creature)
  {
    const list<ItemPtr>& items = creature->get_inventory().get_items_cref();

    for (ItemPtr item : items)
    {
      bool passes_filter = (!filter_v);
      
      if (filter_v)
      {
        list<IItemFilterPtr> filters = *filter_v;
        for (IItemFilterPtr filter : filters)
        {
          passes_filter = filter->passes_filter(item);
          
          if (!passes_filter)
          {
            break;
          }
        }
      }
      
      // This is an item to be identified (it passes all the filters), so identify it.
      if (passes_filter && item) 
      {
        set_item_identified(item, item->get_base_id(), true);
      }
    }    
  }
}

// Identify a particular type of item.
void ItemIdentifier::set_possessions_identified_by_type(CreaturePtr creature, const ItemType item_type)
{
  if (item_type != ITEM_TYPE_NULL)
  {
    list<IItemFilterPtr> item_filter = ItemFilterFactory::create_item_type_filter(item_type);
    set_possessions_identified(creature, &item_filter);
  }
}

// Identify an item
void ItemIdentifier::set_item_identified(ItemPtr item, const string& base_item_id, const bool is_identified) const
{
  ItemPtr base_item = get_base_item(base_item_id);
  
  if (item && base_item)
  {
    // "Base identify" all items of that type.
    base_item->set_item_identified(is_identified);
    
    // Fully identify this particular item.
    item->set_item_identified(true);
    item->set_status_identified(true);
  }
}

// Get whether or not an item is identified.
bool ItemIdentifier::get_item_identified(const string& base_item_id) const
{
  bool item_identified = false;
  ItemPtr item = get_base_item(base_item_id);

  if (item)
  {
    item_identified = item->get_item_identified();
  }
  
  return item_identified;
}

// Get the appropriate description.  If the item is unidentified, use the unidentified_description_sid;
// otherwise, use the regular (identified) one.  Add status, etc.
string ItemIdentifier::get_appropriate_description(ItemPtr item) const
{
  string appropriate_desc;
  ostringstream desc;
  bool item_identified = get_item_identified(item->get_base_id());
  
  if (item)
  {
    if (item_identified || item->get_unidentified_description_sid().empty())
    {
      desc << StringTable::get(item->get_description_sid());

      string synopsis = item->get_synopsis();

      if (!synopsis.empty())
      {
        desc << " " << synopsis;
      }
    }
    else
    {
      desc << StringTable::get(item->get_unidentified_description_sid());
    }
  }
  
  string item_desc = desc.str();
  appropriate_desc = item_desc;

  if (item->get_status_identified())
  {
    ItemStatusTextKeys istk;
    appropriate_desc =  istk.get_item_status_and_description(item->get_status(), appropriate_desc);
  }

  return appropriate_desc;
}

// Get the appropriate usage description.  If the item is unidentified, use the unidentified SID.  Otherwise, use
// the regular SID.  Use status, etc.
string ItemIdentifier::get_appropriate_usage_description(ItemPtr item) const
{
  string appropriate_usage_desc;
  string udesc_sid;
  
  if (item)
  {
    // If the item is identified, or if its identity is not hidden (food,
    // etc)
    if (get_item_identified(item->get_base_id()) || item->get_unidentified_usage_description_sid().empty())
    {
      udesc_sid = item->get_usage_description_sid();
    }
    else
    {
      udesc_sid = item->get_unidentified_usage_description_sid();      
    }
  }

  // The "regular" description is the one displayed in the inventory/equipment
  // screens, etc., and will contain the item synopsis.  The usage description
  // is used when picking up/dropping an item, and so this shouldn't include
  // the synopsis (otherwise the sentences will be full of unnecessary clutter).
  appropriate_usage_desc = StringTable::get(udesc_sid);
  return appropriate_usage_desc;
}

ItemPtr ItemIdentifier::get_base_item(const string& base_item_id) const
{
  ItemPtr item;
  Game& game = Game::instance();
  
  ItemMap item_map = game.get_items_ref();
  item = item_map[base_item_id];
  
  return item;
}
