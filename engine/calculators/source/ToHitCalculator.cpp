#include "CurrentCreatureAbilities.hpp"
#include "SkillManager.hpp"
#include "StatusEffectFactory.hpp"
#include "ToHitCalculator.hpp"
#include "WeaponManager.hpp"

using namespace std;

const int ToHitCalculator::NWP_SKILL_BONUS_DIVISOR = 5;
const int ToHitCalculator::BLESS_STATUS_BONUS = 10;
const int ToHitCalculator::LORE_BONUS_DIVISOR = 10;

map<TileType, SkillType> ToHitCalculator::tt_skill_bonuses = {};
map<MapType, SkillType> ToHitCalculator::mt_skill_bonuses = {};

ToHitCalculator::ToHitCalculator()
: attack_type(AttackType::ATTACK_TYPE_MELEE_PRIMARY)
{
  if (tt_skill_bonuses.empty() || mt_skill_bonuses.empty())
  {
    init_skill_bonuses();
  }
}

ToHitCalculator::ToHitCalculator(const AttackType new_attack_type)
: attack_type(new_attack_type)
{
}

void ToHitCalculator::init_skill_bonuses()
{
  tt_skill_bonuses = { {TileType::TILE_TYPE_FOREST, SkillType::SKILL_GENERAL_FOREST_LORE}, 
                       {TileType::TILE_TYPE_EVERGREEN_TREE, SkillType::SKILL_GENERAL_FOREST_LORE},
                       {TileType::TILE_TYPE_SEA, SkillType::SKILL_GENERAL_OCEAN_LORE},
                       {TileType::TILE_TYPE_RIVER, SkillType::SKILL_GENERAL_OCEAN_LORE},
                       {TileType::TILE_TYPE_MARSH, SkillType::SKILL_GENERAL_MARSH_LORE},
                       {TileType::TILE_TYPE_HILLS, SkillType::SKILL_GENERAL_MOUNTAIN_LORE},
                       {TileType::TILE_TYPE_DESERT, SkillType::SKILL_GENERAL_DESERT_LORE},
                       {TileType::TILE_TYPE_MOUNTAINS, SkillType::SKILL_GENERAL_MOUNTAIN_LORE} };

  mt_skill_bonuses = { {MapType::MAP_TYPE_UNDERWORLD, SkillType::SKILL_GENERAL_DUNGEONEERING}, 
                       {MapType::MAP_TYPE_UNDERWATER, SkillType::SKILL_GENERAL_OCEAN_LORE} };
}

// The level portion of the to-hit bonus is equal to half the creature's
// level, rounded down.
int ToHitCalculator::get_level_bonus(CreaturePtr creature)
{
  int level_bonus = 0;

  if (creature != nullptr)
  {
    level_bonus = creature->get_level().get_current() / 2;
  }

  return level_bonus;
}

int ToHitCalculator::get_weapon_bonus(CreaturePtr creature)
{
  int weapon_bonus = 0;
  
  WeaponManager wm;
  WeaponPtr weapon = wm.get_weapon(creature, attack_type);
  
  SkillManager sm;

  // Apply the weapon modifier.
  SkillType st = SkillType::SKILL_MELEE_UNARMED;
  
  if (attack_type == AttackType::ATTACK_TYPE_RANGED && weapon)
  {
    st = weapon->get_trained_ranged_skill();
  }
  else
  {
    if (weapon)
    {
      st = weapon->get_trained_skill();
    }
  }

  weapon_bonus += (sm.get_skill_value(creature, st) / 2);  
  return weapon_bonus;
}

int ToHitCalculator::get_modifier_bonus(CreaturePtr creature)
{
  int to_hit_bonus = 0;

  if (creature != nullptr)
  {
    const map<double, vector<pair<string, Modifier>>> modifiers = creature->get_active_modifiers();

    for (const auto& mod_pair : modifiers)
    {
      for (const auto& current_mod_pair : mod_pair.second)
      {
        to_hit_bonus += current_mod_pair.second.get_to_hit_modifier();
      }
    }
  }

  return to_hit_bonus;
}

int ToHitCalculator::get_skills_bonus(CreaturePtr creature)
{
  int skills_bonus = 0;

  if (creature != nullptr)
  {
    CurrentCreatureAbilities cca;

    if (!cca.can_see(creature, false))
    {
      int blindfighting_value = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_BLIND_FIGHTING);

      // +1 to hit for every 4 pts of Blindfighting, when blind.
      // This can help negate the base -25 to-hit modifier added by blindness.
      skills_bonus += (blindfighting_value / 4);
    }
  }

  return skills_bonus;
}

int ToHitCalculator::get_status_bonus(CreaturePtr creature)
{
  int status_bonus = 0;

  if (creature != nullptr)
  {
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, attack_type);

    if (weapon != nullptr)
    {
      ItemStatus status = weapon->get_status();

      switch (status)
      {
        case ItemStatus::ITEM_STATUS_BLESSED:
          status_bonus = BLESS_STATUS_BONUS;
          break;
        case ItemStatus::ITEM_STATUS_CURSED:
          status_bonus = BLESS_STATUS_BONUS * -1;
          break;
        case ItemStatus::ITEM_STATUS_UNCURSED:
        default:
          break;
      }
    }
    else
    {
      status_bonus = BLESS_STATUS_BONUS / 2;
    }
  }

  return status_bonus;
}

SkillType ToHitCalculator::get_terrain_lore_skill(CreaturePtr creature, MapPtr map)
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

int ToHitCalculator::get_terrain_bonus(CreaturePtr creature, MapPtr map)
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