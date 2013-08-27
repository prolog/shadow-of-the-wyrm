#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "RechargingEffect.hpp"

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
    Inventory& inv = creature->get_inventory();
    const list<ItemPtr>& items = inv.get_items_cref();

    BOOST_FOREACH(ItemPtr item, items)
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

  if (!recharg_exists && creature->get_is_player())
  {
    add_player_no_wands_message();
  }

  return true;
}

void RechargingEffect::add_player_no_wands_message()
{
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_RECHARGING_PLAYER_NO_WANDS));
  manager.send();
}
