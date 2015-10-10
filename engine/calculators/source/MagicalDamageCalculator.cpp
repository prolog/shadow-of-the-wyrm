#include "Game.hpp"
#include "MagicalDamageCalculator.hpp"

MagicalDamageCalculator::MagicalDamageCalculator()
: DamageCalculator(AttackType::ATTACK_TYPE_MAGICAL)
{
}

// Magical damage =
// Rolled damage * Resistance to that damage
// * 1 (magical damage doesn't slay a particular race)
//
// (Soak is not considered for magical damage - resistances become far more powerful.
//  In essence, all magical attacks are piercing, and we don't need to
//  consider whether an attack is incorporeal.)
int MagicalDamageCalculator::calculate(CreaturePtr defending_creature, const bool slays_creatures_race, const Damage& magical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = base_damage;

  if (defending_creature)
  {
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(magical_damage.get_damage_type());
    
    damage = static_cast<int>(base_damage * resistance_multiplier);
  }
  
  return damage;
}

Damage MagicalDamageCalculator::calculate_base_damage_object(CreaturePtr creature)
{
  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  Spell spell = Game::instance().get_spells_ref().find(sk.get_most_recently_cast_spell_id())->second;

  Damage d;

  if (spell.get_has_damage())
  {
    d = spell.get_damage();
  }

  return d;
}

Damage MagicalDamageCalculator::calculate_base_damage_with_bonuses_or_penalties(CreaturePtr creature)
{
  Damage base_and_bonus = calculate_base_damage_object(creature);

  SpellKnowledge& sk = creature->get_spell_knowledge_ref();
  Spell spell = Game::instance().get_spells_ref().find(sk.get_most_recently_cast_spell_id())->second;
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(sk.get_most_recently_cast_spell_id());

  if (spell.get_allows_bonus())
  {
    base_and_bonus.set_modifier(isk.get_bonus().get_base());
  }

  return base_and_bonus;
}
