#include "Weapon.hpp"

// WEAPON
Weapon::Weapon()
: base_to_hit(0)
{
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

// MELEEWEAPON
MeleeWeapon::MeleeWeapon()
{
}

MeleeWeapon::~MeleeWeapon()
{
}

WeaponStyle MeleeWeapon::get_style() const
{
  return WEAPON_STYLE_MELEE;
}

// RANGEDWEAPON
RangedWeapon::RangedWeapon()
{
}

RangedWeapon::~RangedWeapon()
{
}

WeaponStyle RangedWeapon::get_style() const
{
  return WEAPON_STYLE_RANGED;
}
