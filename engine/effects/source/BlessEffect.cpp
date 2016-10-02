#include "BlessEffect.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"

using namespace std;

BlessEffect::BlessEffect()
{
}

string BlessEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature != nullptr)
  {
    effect_msg = EffectTextKeys::get_bless_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* BlessEffect::clone()
{
  return new BlessEffect(*this);
}

bool BlessEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return bless(creature, BlessEffectType::BLESS_EFFECT_BLESS_ITEMS_OF_TYPE, am);
}

bool BlessEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return bless(creature, BlessEffectType::BLESS_EFFECT_BLESS_ITEM, am);
}

bool BlessEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return bless(creature, BlessEffectType::BLESS_EFFECT_UNCURSE_ITEM, am);
}

bool BlessEffect::bless(CreaturePtr creature, const BlessEffectType bless_type, ActionManager * const am)
{
  bool effect_identified = true;

  // Select an item from the equipment or inventory.
  if (am != nullptr)
  {
    list<IItemFilterPtr> empty_list = ItemFilterFactory::create_empty_filter();
    IInventoryPtr inv = creature->get_inventory();
    ItemPtr selected_item = am->inventory(creature, inv, empty_list, empty_list, false);

    if (selected_item != nullptr)
    {
      ItemType itype = selected_item->get_type();
      const list<ItemPtr> raw_items = inv->get_items_cref();

      // When the effect is blessed, all items of that type are blessed.
      // When uncursed, that item is blessed.
      // When cursed, if that item is cursed, it becomes uncursed.
      switch (bless_type)
      {
        case BlessEffectType::BLESS_EFFECT_BLESS_ITEM:
          selected_item->set_status(ItemStatus::ITEM_STATUS_BLESSED);
          selected_item->set_status_identified(true);
          break;
        case BlessEffectType::BLESS_EFFECT_BLESS_ITEMS_OF_TYPE:
          for (ItemPtr i : raw_items)
          {
            if (i != nullptr)
            {
              if (i->get_type() == itype)
              {
                i->set_status(ItemStatus::ITEM_STATUS_BLESSED);
                i->set_status_identified(true);
              }
            }
          }
          break;
        case BlessEffectType::BLESS_EFFECT_UNCURSE_ITEM:
        default:
          if (selected_item->get_status() == ItemStatus::ITEM_STATUS_CURSED)
          {
            selected_item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
            selected_item->set_status_identified(true);
          }
          break;
      }
    }
  }

  return effect_identified;
}

