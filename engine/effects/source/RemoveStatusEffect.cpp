#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "RemoveStatusEffect.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

RemoveStatusEffect::RemoveStatusEffect(const string& status_ident)
: status_id(status_ident)
{
}

string RemoveStatusEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string no_effect_msg;
  return no_effect_msg;
}

Effect* RemoveStatusEffect::clone()
{
  return new RemoveStatusEffect(*this);
}

bool RemoveStatusEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return remove_status(creature);
}

bool RemoveStatusEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return remove_status(creature);
}

bool RemoveStatusEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return remove_status(creature);
}

bool RemoveStatusEffect::remove_status(CreaturePtr creature)
{
  bool removed_status = false;

  if (creature && creature->has_status(status_id))
  {
    StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(status_id);
    status_effect->undo_change(creature);
    removed_status = true;
  }

  return removed_status;
}
