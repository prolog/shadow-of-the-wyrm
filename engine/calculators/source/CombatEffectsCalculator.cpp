#include "CombatEffectsCalculator.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "WeaponManager.hpp"

const int CombatEffectsCalculator::COMBAT_SKILL_DIVISOR = 10;
const int CombatEffectsCalculator::DEXTERITY_DIVISOR = 5;

int CombatEffectsCalculator::calc_pct_chance_counter_strike(CreaturePtr creature) const
{
  int pct_counter = 0;
  CurrentCreatureAbilities cca;

  if (creature != nullptr && !creature->is_dead() && cca.can_act(creature))
  {
    int combat_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_COMBAT) / COMBAT_SKILL_DIVISOR;
    pct_counter += combat_val;

    // If the creature meets the minimum combat skill threshold for
    // counter-attacking, add the dexterity bonus.
    if (combat_val > 0)
    {
      int dex_val = (creature->get_dexterity().get_current() / DEXTERITY_DIVISOR);
      pct_counter += dex_val;
    }
  }

  return pct_counter;
}

// The chance to knock back via a kick or other tertiary attack is equal
// to half the creature's current strength.
//
// Other melee attacks can also knock back, but require the attacker be
// much larger than the attacked creature. Ranged and magical attacks
// do not knock back.
int CombatEffectsCalculator::calculate_knock_back_pct_chance(const AttackType attack_type, CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int chance = 0;

  int base = -100;
  int bonus = 0;

  if (attack_type == AttackType::ATTACK_TYPE_MELEE_PRIMARY)
  {
    WeaponManager wm;
    SkillType skill = wm.get_skill_type(attacking_creature, attack_type);

    if (skill == SkillType::SKILL_MELEE_UNARMED &&
        attacking_creature && 
        attacking_creature->get_skills().get_value(SkillType::SKILL_MELEE_UNARMED) == Skills::MAX_SKILL_VALUE)
    {
      bonus += 100;
    }
  }
  
  if (attack_type == AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED)
  {
    bonus += 100;
  }
  else
  {
    if (attack_type != AttackType::ATTACK_TYPE_MAGICAL &&
        attack_type != AttackType::ATTACK_TYPE_RANGED &&
        attacking_creature != nullptr && 
        attacked_creature != nullptr)
    {
      int attacked_size = static_cast<int>(attacked_creature->get_size());
      int attacker_size = static_cast<int>(attacking_creature->get_size());

      if (attacker_size - attacked_size >= 2)
      {
        bonus += 100;
      }
    }
  }

  if (attacking_creature != nullptr)
  {
    Statistic strength = attacking_creature->get_strength();
    bonus += (strength.get_current() / 3);
  }

  chance = base + bonus;
  return std::max<int>(chance, 0);
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatEffectsCalculator_test.cpp"
#endif

