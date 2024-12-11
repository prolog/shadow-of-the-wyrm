#include "Creature.hpp"
#include "Skills.hpp"
#include "SkillsCalculator.hpp"

const int SkillsCalculator::HIDDEN_TREASURE_DUNGEONEERING_DIVISOR = 10;

SkillsCalculator::SkillsCalculator()
{
}

SkillsCalculator::~SkillsCalculator()
{
}

Skills SkillsCalculator::calculate_skills(Race* race, Class* char_class)
{
  Skills skills_calculated;

  if (race && char_class)
  {
    skills_calculated = calculate_general_skills      (race, char_class, skills_calculated);
    skills_calculated = calculate_melee_weapon_skills (race, char_class, skills_calculated);
    skills_calculated = calculate_ranged_weapon_skills(race, char_class, skills_calculated);
    skills_calculated = calculate_magic_skills        (race, char_class, skills_calculated);
  }

  return skills_calculated;
}

Skills SkillsCalculator::calculate_general_skills(Race* race, Class* char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(race, char_class, current_skills, static_cast<int>(SkillType::SKILL_GENERAL_BEGIN), static_cast<int>(SkillType::SKILL_GENERAL_LAST));
}

Skills SkillsCalculator::calculate_melee_weapon_skills(Race* race, Class* char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(race, char_class, current_skills, static_cast<int>(SkillType::SKILL_MELEE_BEGIN), static_cast<int>(SkillType::SKILL_MELEE_LAST));
}

Skills SkillsCalculator::calculate_ranged_weapon_skills(Race* race, Class* char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(race, char_class, current_skills, static_cast<int>(SkillType::SKILL_RANGED_BEGIN), static_cast<int>(SkillType::SKILL_RANGED_LAST));
}

Skills SkillsCalculator::calculate_magic_skills(Race* race, Class* char_class, const Skills& current_skills)
{
  return calculate_skills_in_given_range(race, char_class, current_skills, static_cast<int>(SkillType::SKILL_MAGIC_BEGIN), static_cast<int>(SkillType::SKILL_MAGIC_LAST));
}

Skills SkillsCalculator::calculate_skills_in_given_range(Race* race, Class* char_class, const Skills& current_skills, const int first_skill, const int last_skill)
{
  Skills calculated_skills = current_skills;

  Skills race_skills  = race->get_skills();
  Skills class_skills = char_class->get_skills();

  for (int st = first_skill; st < last_skill; st++)
  {
    if (st == 34) continue; // Ignore old mountaineering skill

    SkillType skill_name = static_cast<SkillType>(st);
    Skill* race_skill  = race_skills.get_skill(skill_name);
    Skill* class_skill = class_skills.get_skill(skill_name);

    if (race_skill != nullptr && class_skill != nullptr)
    {
      int race_value = race_skill->get_value();
      int class_value = class_skill->get_value();

      int skill_total = race_value + class_value;
      calculated_skills.set_value(skill_name, skill_total);
    }
  }

  return calculated_skills;
}

int SkillsCalculator::calculate_hidden_treasure_total_skill_value(CreaturePtr creature, const MapType map_type, const int lore_val)
{
  int total = lore_val;

  // Esure the dungeoneering bonus is only applied when on the world map.  Some
  // treasure types (eg shipwrecks) aren't on a new map, but are connected to
  // them.  Without this check, the dungeoneering bonus gets applied twice -
  // once when descending to the overworld map, and again when descending to
  // the associated underwater map.
  if (creature != nullptr && map_type == MapType::MAP_TYPE_WORLD)
  {
    int dungeoneering = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DUNGEONEERING);
    total += (dungeoneering / HIDDEN_TREASURE_DUNGEONEERING_DIVISOR);
  }

  total = std::max<int>(total, 0);
  total = std::min<int>(total, 100);
  return total;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkillsCalculator_test.cpp"
#endif
