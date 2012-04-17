#include "Weapon.hpp"

// WEAPON
Weapon::Weapon()
: base_to_hit(0), trained_skill(SKILL_MELEE_AXES)
{
  type = ITEM_TYPE_WEAPON;
  symbol = ')';
}

ItemType Weapon::get_type() const
{
  return ITEM_TYPE_WEAPON;
}

void Weapon::set_base_to_hit(const int new_base_to_hit)
{
  base_to_hit = new_base_to_hit;
}

int Weapon::get_base_to_hit() const
{
  return base_to_hit;
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
