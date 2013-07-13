#include <boost/make_shared.hpp>
#include "MutenessStatusEffect.hpp"
#include "PoisonStatusEffect.hpp"
#include "StatusEffectFactory.hpp"
#include "StatusTypes.hpp"

using namespace std;

map<DamageType, string> StatusEffectFactory::damage_status_ailments;

StatusEffectFactory::StatusEffectFactory()
{
}

StatusEffectFactory::~StatusEffectFactory()
{
}

void StatusEffectFactory::initialize_damage_status_ailments()
{
  damage_status_ailments.clear();

  damage_status_ailments.insert(make_pair(DAMAGE_TYPE_POISON, StatusIdentifiers::STATUS_ID_POISON));
  damage_status_ailments.insert(make_pair(DAMAGE_TYPE_HOLY, StatusIdentifiers::STATUS_ID_MUTE));
}

StatusEffectPtr StatusEffectFactory::create_effect_for_damage_type(const DamageType dt)
{
  string status_id;

  if (damage_status_ailments.empty())
  {
    initialize_damage_status_ailments();
  }

  map<DamageType, string>::iterator a_it = damage_status_ailments.find(dt);

  if (a_it != damage_status_ailments.end())
  {
    status_id = a_it->second;
  }

  return create_status_effect(status_id);
}

StatusEffectPtr StatusEffectFactory::create_status_effect(const string& status_id)
{
  StatusEffectPtr status_effect;

  if (status_id == StatusIdentifiers::STATUS_ID_POISON)
  {
    status_effect = boost::make_shared<PoisonStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_MUTE)
  {
    status_effect = boost::make_shared<MutenessStatusEffect>();
  }
  else
  {
    // Default case - this basically does nothing for each callable
    // method.
    status_effect = boost::make_shared<StatusEffect>();
  }

  return status_effect;
}
