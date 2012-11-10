#include "Serialize.hpp"
#include "Weapon.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

// WEAPON
Weapon::Weapon()
: difficulty(0), speed(0), trained_skill(SKILL_MELEE_EXOTIC), trained_ranged_skill(SKILL_MELEE_EXOTIC), requires_ranged_weapon(false)
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

void Weapon::set_speed(const int new_speed)
{
  speed = new_speed;
}

int Weapon::get_speed() const
{
  return speed;
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

void Weapon::set_requires_ranged_weapon(const bool new_requires_ranged_weapon)
{
  requires_ranged_weapon = new_requires_ranged_weapon;
}

bool Weapon::get_requires_ranged_weapon() const
{
  return requires_ranged_weapon;
}

bool Weapon::additional_item_attributes_match(boost::shared_ptr<Item> i)
{
  bool match = (i);
  WeaponPtr i_weap = dynamic_pointer_cast<Weapon>(i);
  
  match = (i_weap);
  
  if (i_weap)
  {
    match &= (difficulty           == i_weap->get_difficulty());
    match &= (damage               == i_weap->get_damage()    );
    match &= (trained_skill        == i_weap->get_trained_skill());
    match &= (trained_ranged_skill == i_weap->get_trained_ranged_skill());
  }
  
  return match;
}

bool Weapon::serialize(ostream& stream)
{
  Wearable::serialize(stream);
  Serialize::write_int(stream, difficulty);
  Serialize::write_int(stream, speed);
  damage.serialize(stream);
  Serialize::write_enum(stream, trained_skill);
  Serialize::write_enum(stream, trained_ranged_skill);
  Serialize::write_bool(stream, requires_ranged_weapon);

  return true;
}

bool Weapon::deserialize(istream& stream)
{
  Wearable::deserialize(stream);
  Serialize::read_int(stream, difficulty);
  Serialize::read_int(stream, speed);
  damage.deserialize(stream);
  Serialize::read_enum(stream, trained_skill);
  Serialize::read_enum(stream, trained_ranged_skill);
  Serialize::read_bool(stream, requires_ranged_weapon);

  return true;
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

ClassIdentifier MeleeWeapon::internal_class_identifier() const
{
  return CLASS_ID_MELEE_WEAPON;
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

ClassIdentifier RangedWeapon::internal_class_identifier() const
{
  return CLASS_ID_RANGED_WEAPON;
}

#ifdef UNIT_TESTS
#include "unit_tests/Weapon_test.cpp"
#endif


