#include "Creature.hpp"
#include "Skills.hpp"
#include "SkillsCalculator.hpp"

SkillsCalculator::SkillsCalculator()
{
}

SkillsCalculator::~SkillsCalculator()
{
}

Skills SkillsCalculator::calculate_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class)
{
  Skills skills_calculated;

  if (race && char_class)
  {
    skills_calculated = calculate_general_skills      (creature, race, char_class, skills_calculated);
    skills_calculated = calculate_melee_weapon_skills (creature, race, char_class, skills_calculated);
    skills_calculated = calculate_ranged_weapon_skills(creature, race, char_class, skills_calculated);
    skills_calculated = calculate_magic_skills        (creature, race, char_class, skills_calculated);
  }

  return skills_calculated;
}

Skills SkillsCalculator::calculate_general_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(creature, race, char_class, current_skills, static_cast<int>(SkillType::SKILL_GENERAL_BEGIN), static_cast<int>(SkillType::SKILL_GENERAL_LAST));
}

Skills SkillsCalculator::calculate_melee_weapon_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(creature, race, char_class, current_skills, static_cast<int>(SkillType::SKILL_MELEE_BEGIN), static_cast<int>(SkillType::SKILL_MELEE_LAST));
}

Skills SkillsCalculator::calculate_ranged_weapon_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(creature, race, char_class, current_skills, static_cast<int>(SkillType::SKILL_RANGED_BEGIN), static_cast<int>(SkillType::SKILL_RANGED_LAST));
}

Skills SkillsCalculator::calculate_magic_skills(CreaturePtr creature, RacePtr race, ClassPtr char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(creature, race, char_class, current_skills, static_cast<int>(SkillType::SKILL_MAGIC_BEGIN), static_cast<int>(SkillType::SKILL_MAGIC_LAST));
}

Skills SkillsCalculator::calculate_skills_in_given_range(CreaturePtr creature, RacePtr race, ClassPtr char_class, const Skills& current_skills, const int first_skill, const int last_skill)
{
  // JCD FIXME: Do something with Creature, here!

  Skills calculated_skills = current_skills;

  Skills race_skills  = race->get_skills();
  Skills class_skills = char_class->get_skills();

  for (int st = first_skill; st < last_skill; st++)
  {
    SkillType skill_name = static_cast<SkillType>(st);
    SkillPtr race_skill  = race_skills.get_skill(skill_name);
    SkillPtr class_skill = class_skills.get_skill(skill_name);

    int race_value  = race_skill->get_value();
    int class_value = class_skill->get_value();

    int skill_total = race_value + class_value;
    calculated_skills.set_value(skill_name, skill_total);
  }

  return calculated_skills;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkillsCalculator_test.cpp"
#endif
