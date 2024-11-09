#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "WaterBreathingEffect.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

string WaterBreathingEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string no_effect_msg;

  return no_effect_msg;
}

Effect* WaterBreathingEffect::clone()
{
  return new WaterBreathingEffect(*this);
}

string WaterBreathingEffect::get_status_id() const
{
  return StatusIdentifiers::STATUS_ID_WATER_BREATHING;
}

// When blessed, cure any slowness, and add the WaterBreathing effect.
// Don't allow "double hasting" (being able to cast WaterBreathing while WaterBreathingd),
// or else the game becomes ludicrously easy!
bool WaterBreathingEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

// When uncursed, cure any slowness, or if there is no slowness, add
// the WaterBreathing status effect.
bool WaterBreathingEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  if (creature == nullptr || creature->has_status(StatusIdentifiers::STATUS_ID_WATER_BREATHING))
  {
    return false;
  }

  StatusEffectPtr water_breathing = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_WATER_BREATHING, source_id);
  apply_water_breathing(creature, water_breathing);

  return true;
}

// When cursed, nothing happens.
bool WaterBreathingEffect::effect_cursed(CreaturePtr creature, ActionManager * am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return effect_uncursed(creature, am, affected_coordinate, affected_tile);
}

void WaterBreathingEffect::apply_water_breathing(CreaturePtr creature, StatusEffectPtr water_breathing)
{
  if (creature != nullptr && water_breathing != nullptr)
  {
    water_breathing->apply_change(creature, creature->get_level().get_current());
  }
}