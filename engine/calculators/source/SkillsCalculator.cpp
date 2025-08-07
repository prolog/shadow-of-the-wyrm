#include "Creature.hpp"
#include "Skills.hpp"
#include "SkillsCalculator.hpp"

using std::map;

const int SkillsCalculator::HIDDEN_TREASURE_DUNGEONEERING_DIVISOR = 10;
const int SkillsCalculator::LORE_BONUS_DIVISOR = 10;

map<TileType, SkillType> SkillsCalculator::tt_skill_bonuses = {};
map<MapType, SkillType> SkillsCalculator::mt_skill_bonuses = {};

SkillsCalculator::SkillsCalculator()
{
  if (tt_skill_bonuses.empty() || mt_skill_bonuses.empty())
  {
    init_skill_bonuses();
  }
}

void SkillsCalculator::init_skill_bonuses()
{
  tt_skill_bonuses = { {TileType::TILE_TYPE_FOREST, SkillType::SKILL_GENERAL_FOREST_LORE},
                       {TileType::TILE_TYPE_SEA, SkillType::SKILL_GENERAL_OCEAN_LORE},
                       {TileType::TILE_TYPE_MARSH, SkillType::SKILL_GENERAL_MARSH_LORE},
                       {TileType::TILE_TYPE_HILLS, SkillType::SKILL_GENERAL_MOUNTAIN_LORE},
                       {TileType::TILE_TYPE_DESERT, SkillType::SKILL_GENERAL_DESERT_LORE},
                       {TileType::TILE_TYPE_MOUNTAINS, SkillType::SKILL_GENERAL_MOUNTAIN_LORE} };

  mt_skill_bonuses = { {MapType::MAP_TYPE_UNDERWORLD, SkillType::SKILL_GENERAL_DUNGEONEERING},
                       {MapType::MAP_TYPE_UNDERWATER, SkillType::SKILL_GENERAL_OCEAN_LORE} };
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

SkillType SkillsCalculator::get_terrain_lore_skill(CreaturePtr creature, MapPtr map) const
{
  SkillType sk = SkillType::SKILL_UNDEFINED;

  if (creature != nullptr && map != nullptr)
  {
    TileType tt = map->get_terrain_type();
    auto tt_it = tt_skill_bonuses.find(tt);

    if (tt_it != tt_skill_bonuses.end())
    {
      sk = tt_it->second;
    }
    else
    {
      MapType mt = map->get_map_type();
      auto mt_it = mt_skill_bonuses.find(mt);

      if (mt_it != mt_skill_bonuses.end())
      {
        sk = mt_it->second;
      }
    }
  }

  return sk;
}

int SkillsCalculator::get_terrain_to_hit_bonus(CreaturePtr creature, MapPtr map) const
{
  int bonus = 0;

  if (creature != nullptr && map != nullptr)
  {
    SkillType check_skill = get_terrain_lore_skill(creature, map);

    if (check_skill != SkillType::SKILL_UNDEFINED)
    {
      bonus = creature->get_skills().get_value(check_skill) / LORE_BONUS_DIVISOR;
    }
  }

  return bonus;
}


#ifdef UNIT_TESTS
#include "unit_tests/SkillsCalculator_test.cpp"
#endif
