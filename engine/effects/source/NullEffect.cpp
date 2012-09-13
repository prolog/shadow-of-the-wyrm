#include "Creature.hpp"
#include "NullEffect.hpp"
#include "StringConstants.hpp"

using std::string;

string NullEffect::get_effect_identification_message(boost::shared_ptr<Creature> creature) const
{
  string null_message = StringTable::get(EffectTextKeys::EFFECT_NULL);
  return null_message;
}

Effect* NullEffect::clone()
{
  return new NullEffect(*this);
}

bool NullEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return false;
}

bool NullEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return false;
}

bool NullEffect::effect_cursed(CreaturePtr creature, ActionManager * const am)
{
  return false;
}

