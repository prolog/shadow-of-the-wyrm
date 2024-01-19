#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemFilterFactory.hpp"
#include "MapTypes.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "GlowEffect.hpp"

using namespace std;

string GlowEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_glow_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* GlowEffect::clone()
{
  return new GlowEffect(*this);
}

bool GlowEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return glow(creature, am, true);
}

bool GlowEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return glow(creature, am, true);
}

bool GlowEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return glow(creature, am, false);
}

bool GlowEffect::glow(CreaturePtr creature, ActionManager * const am, const bool glow_on)
{
  bool glow_effect = false;

  if (creature != nullptr)
  {
    IInventoryPtr inv = creature->get_inventory();
    list<IItemFilterPtr> empty_filter = ItemFilterFactory::create_empty_filter();
    ItemPtr item = am->select_equipment_or_inventory_item(creature);

    if (item)
    {
      if (item->get_artifact())
      {
        add_artifact_message(creature);
      }
      else
      {
        glow_item(creature, item, glow_on);
        inv->mark_for_restack();
      }
 
      glow_effect = true;
    }
  }

  if (glow_effect)
  {
    Game::instance().get_sound(creature)->play(SoundEffectID::ITEM_EFFECT);
  }

  return glow_effect;
}

void GlowEffect::add_artifact_message(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(EffectTextKeys::EFFECT_GLOW_ARTIFACT));
    manager.send();
  }
}

void GlowEffect::glow_item(CreaturePtr creature, ItemPtr item, const bool glow_on)
{
  if (creature != nullptr && item != nullptr)
  {
    item->set_glowing(glow_on);

    string message_sid = EffectTextKeys::EFFECT_GLOW_SUCCESS;

    if (glow_on == false)
    {
      message_sid = EffectTextKeys::EFFECT_GLOW_DEAD;
    }

    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }
}