#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "HasteEffect.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

string HasteEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string no_effect_msg;

  return no_effect_msg;
}

Effect* HasteEffect::clone()
{
  return new HasteEffect(*this);
}

// When blessed, cure any slowness, and add the haste effect.
// Don't allow "double hasting" (being able to cast haste while hasted),
// or else the game becomes ludicrously easy!
bool HasteEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  if (creature == nullptr || creature->has_status(StatusIdentifiers::STATUS_ID_HASTE))
  {
    return false;
  }

  if (creature && creature->has_status(StatusIdentifiers::STATUS_ID_SLOWNESS))
  {
    StatusEffectPtr slowness = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_SLOWNESS, source_id);
    slowness->undo_change(creature);
  }

  StatusEffectPtr haste = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_HASTE, source_id);
  haste->apply_change(creature, creature->get_level().get_current());

  return true;
}

// When uncursed, cure any slowness, or if there is no slowness, add
// the haste status effect.
bool HasteEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  if (creature == nullptr || creature->has_status(StatusIdentifiers::STATUS_ID_HASTE))
  {
    return false;
  }

  if (creature->has_status(StatusIdentifiers::STATUS_ID_SLOWNESS))
  {
    StatusEffectPtr slowness = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_SLOWNESS, source_id);
    slowness->undo_change(creature);
  }
  else
  {
    StatusEffectPtr haste = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_HASTE, source_id);
    haste->apply_change(creature, creature->get_level().get_current());
  }

  return true;
}

// When cursed, nothing happens.
bool HasteEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return false;
}

