#include "Weapon.hpp"

// WEAPON
Weapon::Weapon()
: difficulty(0), trained_skill(SKILL_MELEE_EXOTIC), trained_ranged_skill(SKILL_MELEE_EXOTIC)
{
  type = ITEM_TYPE_WEAPON;
  symbol = ')';
}

ItemType Weapon::get_type() const
{
  return ITEM_TYPE_WEAPON;
}

void Weapon::set_difficulty(const int new_difficulty)
{
  difficulty = new_difficulty;
}

int Weapon::get_difficulty() const
{
  return difficulty;
}

void Weapon::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Weapon::get_damage() const
{
  return damage;
}

void Weapon::set_trained_skill(const SkillType new_trained_skill)
{
  trained_skill = new_trained_skill;
}

SkillType Weapon::get_trained_skill() const
{
  return trained_skill;
}

void Weapon::set_trained_ranged_skill(const SkillType new_trained_ranged_skill)
{
  trained_ranged_skill = new_trained_ranged_skill;
}

SkillType Weapon::get_trained_ranged_skill() const
{
  return trained_ranged_skill;
}

// Synchronize the trained skills.
void Weapon::synchronize_trained_skills()
{
  if (get_style() == WEAPON_STYLE_MELEE)
  {
    synchronize_trained_ranged_with_melee();
  }
  else
  {
    synchronize_trained_melee_with_ranged();
  }
}

// Ensure that the ranged trained skill matches up with the melee skill
void Weapon::synchronize_trained_ranged_with_melee()
{
  if (trained_skill == SKILL_MELEE_AXES)
  {
    trained_ranged_skill = SKILL_RANGED_AXES;    
  }
  else if ((trained_skill == SKILL_MELEE_SHORT_BLADES) || (trained_skill == SKILL_MELEE_LONG_BLADES))
  {
    trained_ranged_skill = SKILL_RANGED_BLADES;
  }
  else if (trained_skill == SKILL_MELEE_BLUDGEONS)
  {
    trained_ranged_skill = SKILL_RANGED_BLUDGEONS;
  }
  else if (trained_skill == SKILL_MELEE_DAGGERS)
  {
    trained_ranged_skill = SKILL_RANGED_DAGGERS;
  }
  else if (trained_skill == SKILL_MELEE_SPEARS)
  {
    trained_ranged_skill = SKILL_RANGED_SPEARS;
  }
  else
  {
    trained_ranged_skill = SKILL_RANGED_EXOTIC;
  }
}

// Ensure that the trained melee skill matches up with the ranged skill
void Weapon::synchronize_trained_melee_with_ranged()
{
  if (trained_ranged_skill == SKILL_RANGED_AXES)
  {
    trained_skill = SKILL_MELEE_AXES;
  }
  else if (trained_ranged_skill == SKILL_RANGED_BLADES)
  {
    trained_skill = SKILL_MELEE_LONG_BLADES; // Had to be one of the two...
  }
  else if (trained_ranged_skill == SKILL_RANGED_BLUDGEONS)
  {
    trained_skill = SKILL_MELEE_BLUDGEONS;
  }
  else if (trained_ranged_skill == SKILL_RANGED_DAGGERS)
  {
    trained_skill = SKILL_MELEE_DAGGERS;
  }
  else if (trained_ranged_skill == SKILL_RANGED_SPEARS)
  {
    trained_skill = SKILL_MELEE_SPEARS;
  }
  else
  {
    trained_skill = SKILL_MELEE_EXOTIC;
  }
}

// 

// MELEEWEAPON
MeleeWeapon::MeleeWeapon() 
: Weapon()
{
}

MeleeWeapon::~MeleeWeapon()
{
}

WeaponStyle MeleeWeapon::get_style() const
{
  return WEAPON_STYLE_MELEE;
}

Item* MeleeWeapon::clone()
{
  return new MeleeWeapon(*this);
}

// RANGEDWEAPON
RangedWeapon::RangedWeapon() 
: Weapon()
{
}

RangedWeapon::~RangedWeapon()
{
}

WeaponStyle RangedWeapon::get_style() const
{
  return WEAPON_STYLE_RANGED;
}

Item* RangedWeapon::clone()
{
  return new RangedWeapon(*this);
}
