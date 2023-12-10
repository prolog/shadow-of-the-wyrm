#include "MeleeWeaponRangeCalculator.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Weapon.hpp"
#include "WeaponManager.hpp"

using namespace std;

int MeleeWeaponRangeCalculator::get_primary_melee_range(CreaturePtr creature) const
{
  int range = 0;

  if (creature != nullptr)
  {
    range = 1;

    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);

    if (weapon != nullptr)
    {
      range = weapon->get_range();

      SkillType melee = weapon->get_trained_skill();
      int val = creature->get_skills().get_value(melee);
      if (val == Skills::MAX_SKILL_VALUE &&
          melee == SkillType::SKILL_MELEE_RODS_AND_STAVES)
      {
        range++;
      }
    }
    else
    {
      string range_prop = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_PRIMARY_MELEE_RANGE);

      if (!range_prop.empty())
      {
        range = String::to_int(range_prop);
      }
    }
  }

  return range;
}

#ifdef UNIT_TESTS
#include "unit_tests/MeleeWeaponRangeCalculator_test.cpp"
#endif