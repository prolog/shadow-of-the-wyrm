#pragma once

// If updating this, remember to also update the ancient beasts resource
// strings to define an appropriate creature.
enum struct DamageType
{
  DAMAGE_TYPE_NULL = -1,
  DAMAGE_TYPE_FIRST = 0,
  DAMAGE_TYPE_SLASH = 0,
  DAMAGE_TYPE_PIERCE = 1,
  DAMAGE_TYPE_POUND = 2,
  DAMAGE_TYPE_HEAT = 3,
  DAMAGE_TYPE_COLD = 4,
  DAMAGE_TYPE_ACID = 5,
  DAMAGE_TYPE_POISON = 6,
  DAMAGE_TYPE_HOLY = 7,
  DAMAGE_TYPE_SHADOW = 8,
  DAMAGE_TYPE_ARCANE = 9,
  DAMAGE_TYPE_LIGHTNING = 10,
  DAMAGE_TYPE_MAX = 11
};

constexpr auto CDAMAGE_TYPE_SLASH = 0;
constexpr auto CDAMAGE_TYPE_PIERCE = 1;
constexpr auto CDAMAGE_TYPE_POUND = 2;
constexpr auto CDAMAGE_TYPE_HEAT = 3;
constexpr auto CDAMAGE_TYPE_COLD = 4;
constexpr auto CDAMAGE_TYPE_ACID = 5;
constexpr auto CDAMAGE_TYPE_POISON = 6;
constexpr auto CDAMAGE_TYPE_HOLY = 7;
constexpr auto CDAMAGE_TYPE_SHADOW = 8;
constexpr auto CDAMAGE_TYPE_ARCANE = 9;
constexpr auto CDAMAGE_TYPE_LIGHTNING = 10;


enum struct DamageCategory
{
  DAMAGE_CATEGORY_NULL = -1,
  DAMAGE_CATEGORY_PHYSICAL = 0,
  DAMAGE_CATEGORY_OTHER = 1
};

enum struct DamageFlagType
{
  DAMAGE_FLAG_FIRST = 0,
  DAMAGE_FLAG_CHAOTIC = 0,
  DAMAGE_FLAG_VORPAL = 1,
  DAMAGE_FLAG_DRAINING = 2,
  DAMAGE_FLAG_ETHEREAL = 3,
  DAMAGE_FLAG_PIERCING = 4,
  DAMAGE_FLAG_INCORPOREAL = 5,
  DAMAGE_FLAG_SCYTHING = 6,
  DAMAGE_FLAG_EXPLOSIVE = 7,
  DAMAGE_FLAG_LAST = 7
};
