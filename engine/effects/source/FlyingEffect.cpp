#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "FlyingEffect.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

const int FlyingEffect::EVADE_BONUS = 20;

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
  if (creature == nullptr)
  {
    return false;
  }

  ModifyStatisticsEffect mse;
  Modifier m;

  m.set_evade_modifier(EVADE_BONUS);
  m.set_status(StatusIdentifiers::STATUS_ID_FLYING, true, creature->get_level().get_current());

  mse.set_modifier(m);
  mse.effect(creature, am, ItemStatus::ITEM_STATUS_UNCURSED, affected_coordinate, affected_tile);

  StatusEffectPtr fly = StatusEffectFactory::create_status_effect(creature, StatusIdentifiers::STATUS_ID_FLYING, source_id);
  fly->apply_change(creature, creature->get_level().get_current());

  return true;
}

bool FlyingEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

