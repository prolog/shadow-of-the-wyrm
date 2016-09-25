#include "CombatManager.hpp"
#include "Creature.hpp"
#include "PoisonCalculator.hpp"
#include "PoisonStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"

using namespace std;

PoisonStatusEffect::PoisonStatusEffect()
{
  status_calc = std::make_shared<PoisonCalculator>();
}

void PoisonStatusEffect::tick(CreaturePtr creature) const
{
  CreaturePtr no_creature;
  CombatManager cm;

  PoisonCalculator pc;

  // Poison always deals a single point of damage per minute.
  Damage poison_dmg;
  int damage = pc.calculate_damage_per_tick(creature);
  poison_dmg.set_modifier(damage);
  cm.deal_damage(no_creature, creature, damage, poison_dmg);
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