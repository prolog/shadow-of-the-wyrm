#include "Creature.hpp"
#include "HealingEffect.hpp"

Effect* HealingEffect::clone()
{
  return new HealingEffect(*this);
}

bool HealingEffect::effect_blessed(CreaturePtr creature) const
{
  // JCD FIXME
  return false;
}

bool HealingEffect::effect_uncursed(CreaturePtr creature) const
{
  // JCD FIXME
  return false;
}

bool HealingEffect::effect_cursed(CreaturePtr creature) const
{
  // JCD FIXME
  return false;
}

