#include <boost/foreach.hpp>
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemDisplayFilterFactory.hpp"

using namespace std;

// Identify all the possessions, both equipment and inventory, of a creature.
void ItemIdentifier::set_possessions_identified(CreaturePtr creature, const list<IItemDisplayFilterPtr> * const filter_v)
{
  if (creature)
  {
    set_equipment_identified(creature, filter_v);
    set_inventory_identified(creature, filter_v);
  }
}

// Identify items in the equipment based on the filter provided.  If no filter is provided,
// then identify everything.
void ItemIdentifier::set_equipment_identified(CreaturePtr creature, const list<IItemDisplayFilterPtr> * const filter_v)
{
  if (creature)
  {
    EquipmentMap eq = creature->get_equipment().get_equipment();
        
    BOOST_FOREACH(EquipmentMap::value_type& eq_pair, eq)
    {
      bool passes_filter = (!filter_v);
      
      ItemPtr item = eq_pair.second;

      if (filter_v)
      {
        const list<IItemDisplayFilterPtr> filters = *filter_v;
        BOOST_FOREACH(IItemDisplayFilterPtr filter, filters)
        {
          passes_filter = filter->passes_filter(item);
          
          if (!passes_filter)
          {
            break;
          }
        }
      }
      
      // This is an item to be identified (it passes all the filters), so identify it.
      if (passes_filter) 
      {
        set_item_identified(item->get_base_id(), true);
      }
    }
  }
}

// Identify items in the inventory based on the filter provided.  If no filter is provided,
// then identify everything.
void ItemIdentifier::set_inventory_identified(CreaturePtr creature, const list<IItemDisplayFilterPtr> * const filter_v)
{
  if (creature)
  {
    list<ItemPtr> items = creature->get_inventory().get_items();

    BOOST_FOREACH(ItemPtr item, items)
    {
      bool passes_filter = (!filter_v);
      
      if (filter_v)
      {
        list<IItemDisplayFilterPtr> filters = *filter_v;
        BOOST_FOREACH(IItemDisplayFilterPtr filter, filters)
        {
          passes_filter = filter->passes_filter(item);
          
          if (!passes_filter)
          {
            break;
          }
        }
      }
      
      // This is an item to be identified (it passes all the filters), so identify it.
      if (passes_filter) 
      {
        set_item_identified(item->get_base_id(), true);
      }
    }    
  }
}

// Identify a particular type of item.
void ItemIdentifier::set_possessions_identified_by_type(CreaturePtr creature, const ItemType item_type)
{
  if (item_type != ITEM_TYPE_NULL)
  {
    list<IItemDisplayFilterPtr> item_filter = ItemDisplayFilterFactory::create_item_type_filter(item_type);
    set_possessions_identified(creature, &item_filter);
  }
}

// Identify an item
void ItemIdentifier::set_item_identified(const string& base_item_id, const bool is_identified) const
{
  ItemPtr item = get_base_item(base_item_id);
  
  if (item)
  {
    item->set_item_identified(is_identified);
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

// Get the appropriate description SID.  If the item is unidentified, use the unidentified_description_sid;
// otherwise, use the regular (identified) one.
string ItemIdentifier::get_appropriate_description_sid(const string& base_item_id) const
{
  string desc_sid;
  ItemPtr item = get_base_item(base_item_id);
  
  if (item)
  {
    if (item->get_item_identified())
    {
      desc_sid = item->get_description_sid();
    }
    else
    {
      desc_sid = item->get_unidentified_description_sid();
      
      if (desc_sid.empty())
      {
        // Some items are always identified (food, some weapons, etc).
        desc_sid = item->get_description_sid();
      }
    }
  }
  
  return desc_sid;
}

// Get the appropriate usage description SID.  If the item is unidentified, use the unidentified SID.  Otherwise, use
// the regular SID.
string ItemIdentifier::get_appropriate_usage_description_sid(const string& base_item_id) const
{
  string udesc_sid;
  ItemPtr item = get_base_item(base_item_id);
  
  if (item)
  {
    if (item->get_item_identified())
    {
      udesc_sid = item->get_usage_description_sid();
    }
    else
    {
      udesc_sid = item->get_unidentified_usage_description_sid();
      
      if (udesc_sid.empty())
      {
        // Some items are always identified (food, some weapons, etc).
        udesc_sid = item->get_usage_description_sid();
      }
    }
  }
  
  return udesc_sid;
}

ItemPtr ItemIdentifier::get_base_item(const string& base_item_id) const
{
  ItemPtr item;
  Game* game = Game::instance();
  
  if (game)
  {
    ItemMap item_map = game->get_items_ref();
    item = item_map[base_item_id];
  }
  
  return item;
}
