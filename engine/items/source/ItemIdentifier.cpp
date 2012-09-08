#include "Game.hpp"
#include "ItemIdentifier.hpp"

using namespace std;

void ItemIdentifier::set_item_identified(const string& base_item_id, const bool is_identified) const
{
  ItemPtr item = get_base_item(base_item_id);
  
  if (item)
  {
    item->set_item_identified(is_identified);
  }
}

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
