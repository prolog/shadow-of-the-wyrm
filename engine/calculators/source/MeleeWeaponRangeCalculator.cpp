#include "MeleeWeaponRangeCalculator.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Weapon.hpp"

using namespace std;

int MeleeWeaponRangeCalculator::get_primary_melee_range(CreaturePtr creature) const
{
  int range = 0;

  if (creature != nullptr)
  {
    range = 1;

    const Equipment& equipment = creature->get_equipment();
    WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));

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