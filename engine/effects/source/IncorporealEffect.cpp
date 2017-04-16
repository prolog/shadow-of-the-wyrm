#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "IncorporealEffect.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

string IncorporealEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string no_effect_msg;

  return no_effect_msg;
}

Effect* IncorporealEffect::clone()
{
  return new IncorporealEffect(*this);
}

bool IncorporealEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

// Add incorporeal status.
bool IncorporealEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  StatusEffectPtr incorp = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_INCORPOREAL, source_id);
  incorp->apply_change(creature, creature->get_level().get_current());

  return true;
}

bool IncorporealEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

