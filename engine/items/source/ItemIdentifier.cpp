#include <sstream>
#include "CorpseTextKeys.hpp"
#include "ConsumableConstants.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemStatusTextKeys.hpp"
#include "SkinningConstants.hpp"
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
    const list<ItemPtr>& items = creature->get_inventory()->get_items_cref();

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
    // If the item is a corpse, always create its description from the stored
    // creature description SID.
    string creature_desc_sid = item->get_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID);
    string creature_skin_desc_sid = item->get_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID);

    if (!creature_desc_sid.empty())
    {
      desc << CorpseTextKeys::get_corpse_description(StringTable::get(creature_desc_sid));
    }
    // If the item requires creating a message with substitutions (e.g.,
    // "red dragon skin"), handle that case:
    else if (!creature_skin_desc_sid.empty())
    {
      desc << CorpseTextKeys::get_skin_description(StringTable::get(item->get_description_sid()), StringTable::get(creature_skin_desc_sid));
    }
    // Corpses are a special case.  For all other items, check the identified
    // status, and base the description on whether it's identified or not.
    else if (!item_identified && !item->get_unidentified_description_sid().empty())
    {
      desc << StringTable::get(item->get_unidentified_description_sid());
    }
    else
    {
      desc << StringTable::get(item->get_description_sid());
    }

    // Show the synopsis whenever the item is identified or has no hidden info.
    if (item_identified || item->get_unidentified_description_sid().empty())
    {
      string synopsis = item->get_synopsis();

      if (!synopsis.empty())
      {
        desc << " " << synopsis;
      }
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
  string full_desc;
  
  if (item)
  {
    // If the item is a corpse, always create its description from the stored
    // creature description SID.  Because the overall description (e.g, 
    // "a goblin corpse") isn't a SID, leave udesc_sid empty and populate
    // full_desc, so that the appropriate description can be populated later.
    //
    // The same function is called for both get_appropriate_description and
    // get_appropriate_usage_description because the creature description SID
    // is the value stored on the item, so it will always create items of the
    // style "a foo corpse".
    string creature_desc_sid = item->get_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID);
    string creature_skin_desc_sid = item->get_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID);

    if (!creature_desc_sid.empty())
    {
      full_desc = CorpseTextKeys::get_corpse_description(StringTable::get(creature_desc_sid));
    }
    // If the item requires creating a message with substitutions (e.g.,
    // "red dragon skin"), handle that case:
    else if (!creature_skin_desc_sid.empty())
    {
      full_desc = CorpseTextKeys::get_skin_description(StringTable::get(item->get_description_sid()), StringTable::get(creature_skin_desc_sid));
    }
    //
    // If the item is identified, or if its identity is not hidden (food,
    // etc)
    else if (get_item_identified(item->get_base_id()) || item->get_unidentified_usage_description_sid().empty())
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
  if (full_desc.empty())
  {
    appropriate_usage_desc = StringTable::get(udesc_sid);
  }
  else
  {
    appropriate_usage_desc = full_desc;
  }

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
