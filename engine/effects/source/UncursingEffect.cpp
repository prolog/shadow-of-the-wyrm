#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "UncursingEffect.hpp"

using namespace std;

UncursingEffect::UncursingEffect()
{
}

string UncursingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature != nullptr)
  {
    effect_msg = EffectTextKeys::get_uncursing_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* UncursingEffect::clone()
{
  return new UncursingEffect(*this);
}

bool UncursingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return uncurse(creature, UncursingEffectType::UNCURSING_EFFECT_UNCURSE, UncursingEffectType::UNCURSING_EFFECT_UNCURSE);
}

bool UncursingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return uncurse(creature, UncursingEffectType::UNCURSING_EFFECT_UNCURSE, UncursingEffectType::UNCURSING_EFFECT_NO_EFFECT);
}

bool UncursingEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return uncurse(creature, UncursingEffectType::UNCURSING_EFFECT_NO_EFFECT, UncursingEffectType::UNCURSING_EFFECT_NO_EFFECT);
}

bool UncursingEffect::uncurse(CreaturePtr creature, const UncursingEffectType uet_eq, const UncursingEffectType uet_inv)
{
  bool uncursed = (uet_eq == UncursingEffectType::UNCURSING_EFFECT_UNCURSE || uet_inv == UncursingEffectType::UNCURSING_EFFECT_UNCURSE);

  if (creature != nullptr)
  {
    if (uet_eq == UncursingEffectType::UNCURSING_EFFECT_UNCURSE)
    {
      EquipmentMap raw_eq = creature->get_equipment().get_equipment();

      for (EquipmentMap::const_iterator e_it = raw_eq.begin(); e_it != raw_eq.end(); e_it++)
      {
        EquipmentWornLocation worn_location = e_it->first;
        ItemPtr equipped_item = e_it->second;

        if (equipped_item != nullptr && equipped_item->get_status() == ItemStatus::ITEM_STATUS_CURSED)
        {
          equipped_item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
          equipped_item->set_status_identified(true);
        }
      }
    }

    if (uet_inv == UncursingEffectType::UNCURSING_EFFECT_UNCURSE)
    {
      IInventoryPtr inv = creature->get_inventory();

      if (inv != nullptr)
      {
        list<ItemPtr> items = inv->get_items_ref();

        for (ItemPtr item : items)
        {
          // If the item is cursed, set it to uncursed and status-id'd.
          if (item && item->get_status() == ItemStatus::ITEM_STATUS_CURSED)
          {
            item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
            item->set_status_identified(true);
          }
        }
      }
    }
  }

  return uncursed;
}

