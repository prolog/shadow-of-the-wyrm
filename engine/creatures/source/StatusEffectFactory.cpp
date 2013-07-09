#include <boost/make_shared.hpp>
#include "PoisonStatusEffect.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

StatusEffectFactory::StatusEffectFactory()
{
}

StatusEffectFactory::~StatusEffectFactory()
{
}

StatusEffectPtr StatusEffectFactory::create_effect_for_damage_type(const DamageType dt)
{
  string status_id;

  // JCD FIXME: Once there are more of these, consider putting this into a map.
  if (dt == DAMAGE_TYPE_POISON)
  {
    status_id = StatusIdentifiers::STATUS_ID_POISON;
  }

  return create_status_change(status_id);
}

StatusEffectPtr StatusEffectFactory::create_status_change(const string& status_id)
{
  StatusEffectPtr status_change;

  if (status_id == StatusIdentifiers::STATUS_ID_POISON)
  {
    status_change = boost::make_shared<PoisonStatusEffect>();
  }
  else
  {
    // Default case - this basically does nothing for each callable
    // method.
    status_change = boost::make_shared<StatusEffect>();
  }

  return status_change;
}
