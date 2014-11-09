#include "RNG.hpp"
#include "Serialize.hpp"
#include "Weapon.hpp"

using namespace std;
using std::dynamic_pointer_cast;

// Local enumeration used only for improving weapons.
enum ImproveWeaponType
{
  IMPROVE_WEAPON_TO_HIT = 1,
  IMPROVE_WEAPON_DAMAGE = 2,
  IMPROVE_WEAPON_BOTH   = 3
};

// WEAPON
Weapon::Weapon()
: difficulty(0), speed(0), trained_skill(SKILL_MELEE_EXOTIC), trained_ranged_skill(SKILL_MELEE_EXOTIC), requires_ranged_weapon(false)
{
  type = ITEM_TYPE_WEAPON;
  symbol = ')';
}

bool Weapon::operator==(const Weapon& weapon) const
{
  bool result = true;

  result = result && (difficulty == weapon.difficulty);
  result = result && (speed == weapon.speed);
  result = result && (damage == weapon.damage);
  result = result && (trained_skill == weapon.trained_skill);
  result = result && (trained_ranged_skill == weapon.trained_ranged_skill);
  result = result && (requires_ranged_weapon == weapon.requires_ranged_weapon);
  result = result && (slays_races == weapon.slays_races);

  result = result && (get_style() == weapon.get_style());

  return result;
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

void Weapon::set_slays_races(const vector<string>& new_slays_races)
{
  slays_races = new_slays_races;
}

vector<string> Weapon::get_slays_races() const
{
  return slays_races;
}

bool Weapon::additional_item_attributes_match(std::shared_ptr<Item> i)
{
  bool match = (i != nullptr);
  WeaponPtr i_weap = dynamic_pointer_cast<Weapon>(i);
  
  match = (i_weap != nullptr);
  
  if (i_weap)
  {
    match = match && (difficulty           == i_weap->get_difficulty());
    match = match && (damage               == i_weap->get_damage()    );
    match = match && (trained_skill        == i_weap->get_trained_skill());
    match = match && (trained_ranged_skill == i_weap->get_trained_ranged_skill());
  }
  
  return match;
}

// Enchanting a weapon will enchant either its to-hit, damage,
// or both.  It may also grant resistances.
void Weapon::do_enchant_item(const int points)
{
  if (RNG::percent_chance(50))
  {
    Item::do_enchant_item(points);
  }

  do_improve_item(points);
}

void Weapon::do_smith_item(const int points)
{
  if (RNG::percent_chance(25))
  {
    Item::do_smith_item(points);
  }

  do_improve_item(points);
}

void Weapon::do_improve_item(const int points)
{
  ImproveWeaponType type_of_improve = static_cast<ImproveWeaponType>(RNG::range(IMPROVE_WEAPON_TO_HIT, IMPROVE_WEAPON_BOTH));

  if (points == 1 && type_of_improve == IMPROVE_WEAPON_BOTH)
  {
    // Too few points to do both
    type_of_improve = static_cast<ImproveWeaponType>(RNG::range(IMPROVE_WEAPON_TO_HIT, IMPROVE_WEAPON_BOTH));
  }

  switch (type_of_improve)
  {
    case IMPROVE_WEAPON_TO_HIT:
      set_to_hit(get_to_hit() + static_cast<int>(points * 1.5));
      break;
    case IMPROVE_WEAPON_DAMAGE:
      set_addl_damage(get_addl_damage() + points);
      break;
    case IMPROVE_WEAPON_BOTH:
      set_to_hit(get_to_hit() + points);
      set_addl_damage(get_addl_damage() + (points / 2));
    default:
      break;
  }
}

bool Weapon::serialize(ostream& stream) const
{
  Wearable::serialize(stream);
  Serialize::write_int(stream, difficulty);
  Serialize::write_int(stream, speed);
  damage.serialize(stream);
  Serialize::write_enum(stream, trained_skill);
  Serialize::write_enum(stream, trained_ranged_skill);
  Serialize::write_bool(stream, requires_ranged_weapon);
  Serialize::write_string_vector(stream, slays_races);

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
  Serialize::read_string_vector(stream, slays_races);

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


