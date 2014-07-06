#include "BlindedStatusEffect.hpp"
#include "BloodiedStatusEffect.hpp"
#include "DisfiguredStatusEffect.hpp"
#include "ExposedStatusEffect.hpp"
#include "HasteStatusEffect.hpp"
#include "FlyingStatusEffect.hpp"
#include "IncorporealStatusEffect.hpp"
#include "MutenessStatusEffect.hpp"
#include "ParalysisStatusEffect.hpp"
#include "PoisonStatusEffect.hpp"
#include "SlownessStatusEffect.hpp"
#include "SpellboundStatusEffect.hpp"
#include "StatusEffectFactory.hpp"
#include "StoneStatusEffect.hpp"
#include "StunnedStatusEffect.hpp"
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
  damage_status_ailments = std::map<DamageType, std::string>{{DAMAGE_TYPE_POISON, StatusIdentifiers::STATUS_ID_POISON},
                                                             {DAMAGE_TYPE_HOLY, StatusIdentifiers::STATUS_ID_MUTE},
                                                             {DAMAGE_TYPE_LIGHTNING, StatusIdentifiers::STATUS_ID_PARALYSIS},
                                                             {DAMAGE_TYPE_COLD, StatusIdentifiers::STATUS_ID_SLOWNESS},
                                                             {DAMAGE_TYPE_SHADOW, StatusIdentifiers::STATUS_ID_STONE},
                                                             {DAMAGE_TYPE_SLASH, StatusIdentifiers::STATUS_ID_BLOODIED},
                                                             {DAMAGE_TYPE_POUND, StatusIdentifiers::STATUS_ID_STUNNED},
                                                             {DAMAGE_TYPE_PIERCE, StatusIdentifiers::STATUS_ID_EXPOSED},
                                                             {DAMAGE_TYPE_ACID, StatusIdentifiers::STATUS_ID_DISFIGURED},
                                                             {DAMAGE_TYPE_ARCANE, StatusIdentifiers::STATUS_ID_SPELLBOUND},
                                                             {DAMAGE_TYPE_HEAT, StatusIdentifiers::STATUS_ID_BLINDED}};
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
    status_effect = std::make_shared<PoisonStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_MUTE)
  {
    status_effect = std::make_shared<MutenessStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_PARALYSIS)
  {
    status_effect = std::make_shared<ParalysisStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_SLOWNESS)
  {
    status_effect = std::make_shared<SlownessStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_HASTE)
  {
    status_effect = std::make_shared<HasteStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_STONE)
  {
    status_effect = std::make_shared<StoneStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_BLOODIED)
  {
    status_effect = std::make_shared<BloodiedStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_STUNNED)
  {
    status_effect = std::make_shared<StunnedStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_EXPOSED)
  {
    status_effect = std::make_shared<ExposedStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_DISFIGURED)
  {
    status_effect = std::make_shared<DisfiguredStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_SPELLBOUND)
  {
    status_effect = std::make_shared<SpellboundStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_BLINDED)
  {
    status_effect = std::make_shared<BlindedStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_INCORPOREAL)
  {
    status_effect = std::make_shared<IncorporealStatusEffect>();
  }
  else if (status_id == StatusIdentifiers::STATUS_ID_FLYING)
  {
    status_effect = std::make_shared<FlyingStatusEffect>();
  }
  else
  {
    // Default case - this basically does nothing for each callable
    // method.
    status_effect = std::make_shared<StatusEffect>();
  }

  return status_effect;
}
