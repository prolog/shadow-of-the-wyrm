#include <boost/make_shared.hpp>
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

bool IncorporealEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return effect_uncursed(creature, am);
}

// Add incorporeal status.
bool IncorporealEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  StatusEffectPtr incorp = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  incorp->apply_change(creature);

  return true;
}

bool IncorporealEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return effect_uncursed(creature, am);
}

