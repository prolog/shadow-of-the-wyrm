#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "NullEffect.hpp"

using std::string;

string NullEffect::get_effect_identification_message(std::shared_ptr<Creature> creature) const
{
  string null_message = StringTable::get(EffectTextKeys::EFFECT_NULL);
  return null_message;
}

Effect* NullEffect::clone()
{
  return new NullEffect(*this);
}

bool NullEffect::effect_blessed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return false;
}

bool NullEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return false;
}

bool NullEffect::effect_cursed(CreaturePtr creature, ActionManager * const am, const Coordinate& affected_coordinate, TilePtr affected_tile)
{
  return false;
}
