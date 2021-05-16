#include "UnarmedCombatCalculator.hpp"
#include "WeaponManager.hpp"

const int UnarmedCombatCalculator::UNARMED_SKILL_KICK_SUBTRAHEND = 35;

bool UnarmedCombatCalculator::is_attack_unarmed(CreaturePtr creature, AttackType attack_type) const
{
  bool is_unarmed = false;

  if (creature != nullptr)
  {
    if (attack_type == AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED)
    {
      is_unarmed = true;
    }
    else
    {
      if (attack_type == AttackType::ATTACK_TYPE_MELEE_PRIMARY || attack_type == AttackType::ATTACK_TYPE_MELEE_SECONDARY)
      {
        WeaponManager wm;
        WeaponPtr weapon = wm.get_weapon(creature, attack_type);

        if (weapon == nullptr || weapon->get_trained_skill() == SkillType::SKILL_MELEE_UNARMED)
        {
          is_unarmed = true;
        }
      }
    }
  }

  return is_unarmed;
}

int UnarmedCombatCalculator::calculate_pct_chance_free_kick(CreaturePtr creature) const
{
  int pct_free_kick = 0;

  if (creature != nullptr)
  {
    pct_free_kick = creature->get_skills().get_value(SkillType::SKILL_MELEE_UNARMED) - UNARMED_SKILL_KICK_SUBTRAHEND;
    pct_free_kick = std::max<int>(pct_free_kick, 0);
  }

  return pct_free_kick;
}

#ifdef UNIT_TESTS
#include "unit_tests/UnarmedCombatCalculator_test.cpp"
#endif
