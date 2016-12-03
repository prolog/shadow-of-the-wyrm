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
      auto i_it = items.begin();

      while (i_it != items.end())
      {
        ItemPtr item = *i_it;
        bool processed = false;

        // Artifacts cannot be destroyed/altered.
        if (!item->get_artifact() && affects_item(item) && RNG::percent_chance(pct_chance))
        {
          process_item(item);
          processed = true;

          string message = get_item_processed_message(item);

          if (!message.empty())
          {
            manager.add_new_message(message);
            manager.send();
          }
        }

        if (processed && destroy_item())
        {
          i_it = items.erase(i_it);
        }
        else
        {
          ++i_it;
        }
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

string TileDamageProcessor::get_item_processed_message(ItemPtr item)
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

bool TileDamageProcessor::destroy_item() const
{
  return true;
}

void TileDamageProcessor::process_item(ItemPtr item)
{
}
