#include "ActionManager.hpp"
#include "Conversion.hpp"
#include "EffectTextKeys.hpp"
#include "EnchantingEffect.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using namespace std;

EnchantingEffect::EnchantingEffect()
: item_status_multipliers({ { ItemStatus::ITEM_STATUS_BLESSED, 1.5f }, { ItemStatus::ITEM_STATUS_UNCURSED, 1.0f }, { ItemStatus::ITEM_STATUS_CURSED, -1.0f } })
{
}

string EnchantingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
  }

  return effect_msg;
}

Effect* EnchantingEffect::clone()
{
  return new EnchantingEffect(*this);
}

bool EnchantingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return enchant(creature, am, ItemStatus::ITEM_STATUS_BLESSED);
}

bool EnchantingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return enchant(creature, am, ItemStatus::ITEM_STATUS_UNCURSED);
}

bool EnchantingEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return enchant(creature, am, ItemStatus::ITEM_STATUS_CURSED);
}

// Select an item to enchant.
bool EnchantingEffect::enchant(CreaturePtr creature, ActionManager* const am, const ItemStatus item_status)
{
  if (creature == nullptr || am == nullptr)
  {
    return false;
  }

  bool is_player = creature->get_is_player();

  if (is_player && !creature->has_items())
  {
    add_sid_message(creature, EffectTextKeys::EFFECT_NO_ITEMS_TO_ENCHANT);
    return true;
  }

  list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
  ItemPtr item = am->select_equipment_or_inventory_item(creature);

  if (item != nullptr)
  {
    if (is_player && item->get_artifact())
    {
      add_sid_message(creature, EffectTextKeys::EFFECT_ATTEMPT_ENCHANT_ARTIFACT);
    }
    else if (!item->get_artifact())
    {
      ItemIdentifier iid;
      float enchantment_multiplier = item_status_multipliers[item_status];
      bool can_enchant = item->can_enchant();

      // If it can't be enchanted, display a message.
      if (!can_enchant)
      {
        add_message(creature, EffectTextKeys::get_max_enchanted_message(iid.get_appropriate_usage_description(item)));
      }
      // If it can, enchant it, and display a message.
      else
      {
        ItemEnchantmentCalculator iec;
        int pct_chance_brand = iec.calculate_pct_chance_brand(enchantment_multiplier, item);
        item->enchant(pct_chance_brand, enchantment_multiplier);

        if (item_status == ItemStatus::ITEM_STATUS_CURSED)
        {
          add_message(creature, EffectTextKeys::get_cursed_enchant_message(iid.get_appropriate_usage_description(item)));
        }
        else
        {
          add_message(creature, EffectTextKeys::get_enchant_message(iid.get_appropriate_usage_description(item)));
        }
      }
    }

    return true;
  }

  return false;
}

void EnchantingEffect::add_sid_message(CreaturePtr creature, const string& msg_sid)
{
  add_message(creature, StringTable::get(msg_sid));
}

// All the enchanting messages should be player-only.
void EnchantingEffect::add_message(CreaturePtr creature, const string& msg)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_message(msg);
  manager.send();
}