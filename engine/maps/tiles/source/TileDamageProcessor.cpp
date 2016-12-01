#include "ItemDescriber.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "TileDamageProcessor.hpp"

using namespace std;

void TileDamageProcessor::process(TilePtr tile, CreaturePtr creature)
{
  if (tile != nullptr)
  {
    IInventoryPtr inv = tile->get_items();
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

    if (inv != nullptr)
    {
      list<ItemPtr>& items = inv->get_items_ref();
      int pct_chance = get_pct_chance();
      vector<string> destroyed_items;

      for (ItemPtr item : items)
      {
        // Artifacts cannot be destroyed.
        if (!item->get_artifact() && affects_item(item) && RNG::percent_chance(pct_chance))
        {
          // Mark the item for destruction, and add a message.
          destroyed_items.push_back(item->get_id());
          string message = get_item_destruction_message(item);

          if (!message.empty())
          {
            manager.add_new_message(message);
            manager.send();
          }
        }
      }

      for (const string& id : destroyed_items)
      {
        inv->remove(id);
      }
    }
    }
}

int TileDamageProcessor::get_pct_chance() const
{
  return 0;
}

string TileDamageProcessor::get_message_sid() const
{
  string no_msg;
  return no_msg;
}

string TileDamageProcessor::get_item_destruction_message(ItemPtr item)
{
  string message;

  if (item != nullptr)
  {
    message = StringTable::get(get_message_sid());

    if (!message.empty())
    {
      ItemDescriber id(item);
      string item_desc = id.describe_usage();
      boost::replace_first(message, "%s", item_desc);
      message[0] = toupper(message[0]);
    }
  }

  return message;
}