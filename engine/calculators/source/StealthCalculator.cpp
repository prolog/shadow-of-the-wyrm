#include "StealthCalculator.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"

// Creatures that have been victims of sneak attacks in the past are
// on their guard and cannot be backstabbed again.
//
// Otherwise:
//
// Hidden creatures always sneak attack.
//
// When not hidden, there is a small (Stealth/5 %) chance of a creature 
// getting in a sneak attack, if the creature has any Stealth skill.  The 
// minimum value is always 1%.
//
// When the melee daggers skill is 100, there is a 30% chance of a sneak
// attack.  This adds on to the existing chance from stealth.
//
// At 100 Stealth and 100 Daggers, the chance to sneak attack is therefore
// 50%.
int StealthCalculator::calculate_pct_chance_sneak_attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature) const
{
  int pct_chance = 0;

  if (attacking_creature != nullptr && attacked_creature != nullptr)
  {
    if (String::to_bool(attacked_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_BACKSTABBED)) == false)
    {
      if (attacking_creature->has_status(StatusIdentifiers::STATUS_ID_HIDE))
      {
        pct_chance = 100;
      }
      else
      {
        int stealth_val = attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_STEALTH);

        if (stealth_val > 0)
        {
          pct_chance = std::max<int>(stealth_val / 5, 1);
        }

        int daggers_val = attacking_creature->get_skills().get_value(SkillType::SKILL_MELEE_DAGGERS);

        if (daggers_val == 100)
        {
          pct_chance += 30;
        }
      }
    }
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/StealthCalculator_test.cpp"
#endif

