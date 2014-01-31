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
    add_message(creature, EffectTextKeys::EFFECT_NO_ITEMS_TO_ENCHANT);
    return true;
  }

  list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
  ItemPtr item = am->inventory(creature, creature->get_inventory(), no_filter, false);

  if (item != nullptr)
  {
    if (is_player && item->get_artifact())
    {
      add_message(creature, EffectTextKeys::EFFECT_ATTEMPT_ENCHANT_ARTIFACT);
    }
    else if (!item->get_artifact())
    {
      float enchantment_multiplier = item_status_multipliers[item_status];

      // JCD TODO: check the item to see if it can be enchanted.
      bool can_enchant = item->can_enchant();

      // If it can't, display a message.
      if (!can_enchant)
      {
        // ...
      }
      // If it can, enchant it, and display a message.
      else
      {
        item->enchant();
      }
    }

    return true;
  }

  return false;
}

void EnchantingEffect::add_message(CreaturePtr creature, const string& msg_sid)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(StringTable::get(msg_sid));
  manager.send();
}