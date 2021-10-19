#include "Game.hpp"
#include "MagicalDamageCalculator.hpp"

const int MagicalDamageCalculator::MAGICAL_DAMAGE_SKILL_DIVISOR = 10;
const int MagicalDamageCalculator::MAGICAL_DAMAGE_STAT_DIVISOR = 5;

MagicalDamageCalculator::MagicalDamageCalculator(const PhaseOfMoonType new_pom)
: DamageCalculator(AttackType::ATTACK_TYPE_MAGICAL, new_pom)
{
}

// Magical damage =
// Rolled damage * Resistance to that damage * any phase of moon multiplier
// * any sneak multiplier * 1 (magical damage doesn't slay a particular 
// race)
//
// (Soak is not considered for magical damage - resistances become far more powerful.
//  In essence, all magical attacks are piercing, and we don't need to
//  consider whether an attack is incorporeal.)
int MagicalDamageCalculator::calculate(CreaturePtr defending_creature, const bool sneak_attack, const bool slays_creatures_race, const Damage& magical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = base_damage;

  if (defending_creature)
  {
    DamageType damage_type = magical_damage.get_damage_type();
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(damage_type);
    double pom_multiplier = get_phase_of_moon_multiplier(damage_type, pom_type);
    double sneak_multiplier = get_sneak_attack_multiplier(sneak_attack);
    
    damage = static_cast<int>(base_damage * std::max(resistance_multiplier, 0.0) * pom_multiplier * sneak_multiplier);
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
    if (creature != nullptr)
    {
      int modifier = isk.get_bonus().get_base();
      base_and_bonus.set_effect_bonus(base_and_bonus.get_effect_bonus() + modifier);

      modifier += get_skill_modifier(creature, spell.get_magic_category());
      modifier += get_stat_modifier(creature);

      base_and_bonus.set_modifier(modifier);
    }
  }

  return base_and_bonus;
}

int MagicalDamageCalculator::get_skill_modifier(CreaturePtr creature, const SkillType magic_category)
{
  int skill_mod = 0;

  if (creature != nullptr)
  {
    skill_mod += (creature->get_skills().get_value(SkillType::SKILL_GENERAL_MAGIC) / MAGICAL_DAMAGE_SKILL_DIVISOR);
    skill_mod += (creature->get_skills().get_value(magic_category) / MAGICAL_DAMAGE_SKILL_DIVISOR);
  }

  return skill_mod;
}

int MagicalDamageCalculator::get_stat_modifier(CreaturePtr creature)
{
  int stat_mod = 0;

  if (creature != nullptr)
  {
    int int_will = (creature->get_intelligence().get_current() + creature->get_willpower().get_current()) / 2;
    stat_mod = (int_will / MAGICAL_DAMAGE_STAT_DIVISOR);
  }

  return stat_mod;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicalDamageCalculator_test.cpp"
#endif