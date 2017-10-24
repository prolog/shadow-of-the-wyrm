#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "FlyingEffect.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

string FlyingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string no_effect_msg;

  return no_effect_msg;
}

Effect* FlyingEffect::clone()
{
  return new FlyingEffect(*this);
}

bool FlyingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

bool FlyingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  StatusEffectPtr fly = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_FLYING, source_id);
  fly->apply_change(creature, creature->get_level().get_current());

  return true;
}

bool FlyingEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

