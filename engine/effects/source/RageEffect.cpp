#include "RageEffect.hpp"
#include "EffectTextKeys.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

// Will be handled by applying the rage status effect.
string RageEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string no_effect;

  return no_effect;
}

Effect* RageEffect::clone()
{
  return new RageEffect(*this);
}

bool RageEffect::rage(CreaturePtr creature)
{
  bool effect_applied = false;
  string rage_s = StatusIdentifiers::STATUS_ID_RAGE;

  if (creature != nullptr && !creature->has_status(rage_s))
  {
    StatusEffectPtr rage = StatusEffectFactory::create_status_effect(rage_s, source_id);

    if (rage != nullptr)
    {
      rage->apply_change(creature, creature->get_level().get_current());
      effect_applied = true;
    }
  }

  return effect_applied;
}

bool RageEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return rage(creature); // JCD FIXME
}

bool RageEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return rage(creature); // JCD FIXME
}

bool RageEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return rage(creature); // JCD FIXME
}

// JCD FIXME unit tests
