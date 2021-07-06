#include "CombatManager.hpp"
#include "Creature.hpp"
#include "DeathSourceTextKeys.hpp"
#include "PoisonCalculator.hpp"
#include "PoisonStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"

using namespace std;

PoisonStatusEffect::PoisonStatusEffect()
{
  status_calc = std::make_shared<PoisonCalculator>();
}

void PoisonStatusEffect::tick(CreaturePtr creature, const int danger_level) const
{
  CreaturePtr no_creature;
  CombatManager cm;

  PoisonCalculator pc;

  // Poison deals damage over time.  The more powerful the creature (ie, higher
  // the danger level), the more damage is dealt).
  Damage poison_dmg;
  poison_dmg.set_damage_type(DamageType::DAMAGE_TYPE_POISON);
  int damage = pc.calculate_damage_per_tick(creature, danger_level);
  poison_dmg.set_modifier(damage);
  cm.deal_damage(no_creature, creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, source_id, damage, poison_dmg, "", DeathSourceTextKeys::DEATH_SOURCE_POISON);
}

string PoisonStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED);
  return message;
}

string PoisonStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_poisoned_message(creature);
  return message;
}

string PoisonStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISON_CURED);
  return message;
}

string PoisonStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_poison_message(creature);
  return message;
}

string PoisonStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_POISON;
}