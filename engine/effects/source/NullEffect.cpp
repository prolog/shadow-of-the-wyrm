#include "Creature.hpp"
#include "NullEffect.hpp"

Effect* NullEffect::clone()
{
  return new NullEffect(*this);
}

bool NullEffect::effect_blessed(CreaturePtr creature) const
{
  return false;
}

bool NullEffect::effect_uncursed(CreaturePtr creature) const
{
  return false;
}

bool NullEffect::effect_cursed(CreaturePtr creature) const
{
  return false;
}

