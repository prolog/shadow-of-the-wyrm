#include "FeatureDescriber.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "ItemDescriber.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "TileDamageProcessor.hpp"

using namespace std;

void TileDamageProcessor::process(MapPtr map, TilePtr tile, CreaturePtr creature)
{
  if (map != nullptr && tile != nullptr && creature != nullptr)
  {
    IInventoryPtr inv = tile->get_items();
    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    FeaturePtr feature = tile->get_feature();

    process_feature(creature, map, tile, feature, manager);
    process_items(inv, manager);
  }
}

void TileDamageProcessor::process_feature(CreaturePtr creature, MapPtr map, TilePtr tile, FeaturePtr feature, IMessageManager& manager)
{
  if (creature != nullptr && map != nullptr && tile != nullptr && feature != nullptr)
  {
    if (affects_feature(feature) &&
      RNG::percent_chance(get_pct_chance()))
    {
      FeatureManipulatorPtr manip = IFeatureManipulatorFactory::create_manipulator(feature);
      manip->desecrate(creature, map);
      tile->remove_feature();

      string message = get_feature_processed_message(feature);

      if (!message.empty())
      {
        manager.add_new_message(message);
        manager.send();
      }
    }
  }
}

void TileDamageProcessor::process_items(IInventoryPtr inv, IMessageManager& manager)
{
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
      message[0] = static_cast<char>(toupper(message[0]));
    }
  }

  return message;
}

string TileDamageProcessor::get_feature_processed_message(FeaturePtr feature)
{
  string message;

  if (feature != nullptr)
  {
    message = StringTable::get(get_message_sid());

    if (!message.empty())
    {
      FeatureDescriber fd(feature);
      string feat_desc = fd.describe();
      boost::replace_first(message, "%s", feat_desc);

      message[0] = static_cast<char>(toupper(message[0]));
    }
  }

  return message;
}

bool TileDamageProcessor::destroy_item() const
{
  return true;
}

void TileDamageProcessor::process_item(ItemPtr /*item*/)
{
}

bool TileDamageProcessor::affects_item(ItemPtr item)
{
  bool affects_it = false;

  if (item != nullptr)
  {
    affects_it = affects_material(item->get_material_type());
  }

  return affects_it;
}

bool TileDamageProcessor::affects_feature(FeaturePtr feature)
{
  bool affects_ft = false;

  if (feature != nullptr)
  {
    affects_ft = affects_material(feature->get_material_type());
  }

  return affects_ft;
}
