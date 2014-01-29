#include "ActionManager.hpp"
#include "EffectTextKeys.hpp"
#include "EnchantingEffect.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

EnchantingEffect::EnchantingEffect()
: item_status_multipliers({{ ITEM_STATUS_BLESSED, 1.5f }, {ITEM_STATUS_UNCURSED, 1.0f}, {ITEM_STATUS_CURSED, -1.0f}})
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

bool EnchantingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return enchant(creature, am, ITEM_STATUS_BLESSED);
}

bool EnchantingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return enchant(creature, am, ITEM_STATUS_UNCURSED);
}

bool EnchantingEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  return enchant(creature, am, ITEM_STATUS_CURSED);
}

// Select an item to enchant.
bool EnchantingEffect::enchant(CreaturePtr creature, ActionManager * const am, const ItemStatus item_status)
{
  bool is_player = creature->get_is_player();

  if (is_player && !creature->has_items())
  {
    add_player_no_items_message();
    return true;
  }

  list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
  ItemPtr item = am->inventory(creature, creature->get_inventory(), no_filter, false);

  if (item != nullptr)
  {
    if (is_player && item->get_artifact())
    {
      add_player_enchant_artifact_message();
    }
    else if (!item->get_artifact())
    {
      float enchantment_multiplier = item_status_multipliers[item_status];

      // JCD TODO: check the item to see if it can be enchanted.
      // If it can't, display a message.
      // If it can, enchant it, and display a message.
    }

    return true;
  }

  return false;
}

// Add a message if the player has no equipment or items.
void EnchantingEffect::add_player_no_items_message()
{
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_NO_ITEMS_TO_ENCHANT));
  manager.send();
}

// Add a message if the player tries to enchant an artifact -
// artifacts cannot be enchanted.
void EnchantingEffect::add_player_enchant_artifact_message()
{
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_ATTEMPT_ENCHANT_ARTIFACT));
  manager.send();
}