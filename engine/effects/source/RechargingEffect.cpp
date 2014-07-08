#include "ActionManager.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "ItemIdentifier.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "RechargingEffect.hpp"
#include "RNG.hpp"

using namespace std;

RechargingEffect::RechargingEffect()
{
}

string RechargingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
  }

  return effect_msg;
}

Effect* RechargingEffect::clone()
{
  return new RechargingEffect(*this);
}

// Check to see if the creature has any rechargable items in its inventory.
bool RechargingEffect::has_rechargables(CreaturePtr creature)
{
  bool items_exist = false;

  if (creature)
  {
    IInventoryPtr inv = creature->get_inventory();
    const list<ItemPtr>& items = inv->get_items_cref();

    for (ItemPtr item : items)
    {
      if (item && item->get_type() == ITEM_TYPE_WAND)
      {
        return true;
      }
    }
  }

  return items_exist;
}

bool RechargingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return recharge(creature, am, ITEM_STATUS_BLESSED);
}

bool RechargingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return recharge(creature, am, ITEM_STATUS_UNCURSED);
}

bool RechargingEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  return recharge(creature, am, ITEM_STATUS_CURSED);
}

bool RechargingEffect::recharge(CreaturePtr creature, ActionManager * const am, const ItemStatus item_status)
{
  bool recharg_exists = has_rechargables(creature);
  bool effect_identified = false;

  if (!recharg_exists && creature->get_is_player())
  {
    add_player_no_wands_message();
    effect_identified = true;
  }
  else
  {
    list<IItemFilterPtr> wand_filter = ItemFilterFactory::create_item_type_filter(ITEM_TYPE_WAND);

    ItemPtr item = am->inventory(creature, creature->get_inventory(), wand_filter, false);
    WandPtr wand = std::dynamic_pointer_cast<Wand>(item);

    if (wand)
    {
      pair<int, int> charge_range = get_charges_range(item_status);
      int additional_charges = RNG::range(charge_range.first, charge_range.second);
      Statistic num_charges = wand->get_charges();

      if (num_charges.get_current() == num_charges.get_base())
      {
        // The wand is already fully loaded.
        add_recharge_already_full_message(creature, wand);
      }
      else
      {
        // Recharge the wand, ensuring that we don't go over the wand's
        // actual capacity.
        int max_charges = num_charges.get_base();
        int new_charges = std::min<int>(max_charges, num_charges.get_current() + additional_charges);
        num_charges.set_current(new_charges);
        wand->set_charges(num_charges);

        add_recharge_message(creature, wand);
      }

      effect_identified = true;
    }
  }

  return effect_identified;
}

void RechargingEffect::add_player_no_wands_message()
{
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_RECHARGING_PLAYER_NO_WANDS));
  manager.send();
}

void RechargingEffect::add_recharge_already_full_message(CreaturePtr creature, WandPtr wand)
{
  ItemIdentifier item_id;
  string wand_desc = item_id.get_appropriate_usage_description(wand);

  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(EffectTextKeys::get_wand_recharge_already_full_message(wand_desc));
  manager.send();
}

void RechargingEffect::add_recharge_message(CreaturePtr creature, WandPtr wand)
{
  ItemIdentifier item_id;
  string wand_desc = item_id.get_appropriate_usage_description(wand);

  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(EffectTextKeys::get_wand_recharge_message(wand_desc));
  manager.send();
}

// Get the (min,max) range for the random number of charges, based on the
// item status.
pair<int, int> RechargingEffect::get_charges_range(const ItemStatus item_status)
{
  pair<int, int> charge_range;

  switch(item_status)
  {
    case ITEM_STATUS_CURSED:
      charge_range.first = 1;
      charge_range.second = 2;
      break;
    case ITEM_STATUS_UNCURSED:
      charge_range.first = 1;
      charge_range.second = 4;
      break;
    case ITEM_STATUS_BLESSED:
      charge_range.first = 2;
      charge_range.second = 5;
    default:
      break;
  }

  return charge_range;
}