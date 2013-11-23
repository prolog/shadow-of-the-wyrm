#include <string>
#include <sstream>
#include "Conversion.hpp"
#include "Damage.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

Damage::Damage()
: Dice(0, 0, 0), damage_type(DAMAGE_TYPE_SLASH), chaotic(false)
{
}

Damage::Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const bool chaos)
: Dice(dice, sides, mod), damage_type(dtype), chaotic(chaos)
{
}

Damage::Damage(const Damage& d)
: Dice(d.num_dice, d.dice_sides, d.modifier), damage_type(d.damage_type), chaotic(d.chaotic)
{
  DamagePtr addl_damage = d.get_additional_damage();
  
  if (addl_damage)
  {
    additional_damage = std::shared_ptr<Damage>(new Damage(*addl_damage));
  }
}

Damage& Damage::operator=(const Damage& d)
{
  if (this != &d)
  {
    num_dice    = d.num_dice;
    dice_sides  = d.dice_sides;
    modifier    = d.modifier;
    damage_type = d.damage_type;
    chaotic     = d.chaotic;
    
    DamagePtr addl_damage = d.get_additional_damage();
    
    if (addl_damage)
    {
      additional_damage = std::shared_ptr<Damage>(new Damage(*d.get_additional_damage()));
    }
  }
  
  return *this;
}

bool Damage::operator==(const Damage& d) const
{
  if (this != &d)
  {
    bool match = true;
    
    match = match && (num_dice    == d.get_num_dice()   );
    match = match && (dice_sides  == d.get_dice_sides() );
    match = match && (modifier    == d.get_modifier()   );

    // bypass the "chaotic" flag.  otherwise, unit tests fail
    // roughly 50% of the time when chaotic is on. :)
    match = match && (damage_type == d.damage_type      );

    match = match && (chaotic     == d.get_chaotic()    );
    
    DamagePtr d_add_damage = d.get_additional_damage();
    bool add_damage_matches = true;
    
    if (additional_damage && d_add_damage)
    {
      add_damage_matches = (*additional_damage == *d_add_damage);
      match = match && add_damage_matches;
    }
    
    return match;
  }
  
  return false;
}

Damage::~Damage()
{
}

void Damage::set_damage_type(const DamageType new_damage_type)
{
  damage_type = new_damage_type;
}

DamageType Damage::get_damage_type() const
{
  if (!chaotic || RNG::percent_chance(50))
  {
    return damage_type;
  }
  else
  {
    return static_cast<DamageType>(RNG::range(DAMAGE_TYPE_SLASH, DAMAGE_TYPE_MAX-1));
  }
}

void Damage::set_additional_damage(DamagePtr new_additional_damage)
{
  additional_damage = new_additional_damage;
}

bool Damage::has_additional_damage() const
{
  return (additional_damage != nullptr);
}

DamagePtr Damage::get_additional_damage() const
{
  return additional_damage;
}

void Damage::set_chaotic(const bool new_chaotic)
{
  chaotic = new_chaotic;
}

bool Damage::get_chaotic() const
{
  return chaotic;
}

string Damage::str() const
{
  ostringstream ss;
  string modifier_s;
  
  ss << num_dice << "d" << dice_sides;
  
  if (modifier > 0)
  {
    modifier_s = "+";
  }
  else if (modifier < 0)
  {
    modifier_s = "-";
  }
  
  if (!modifier_s.empty())
  {
    ss << modifier_s << modifier;
  }
  
  if (additional_damage)
  {
    ss << "+" << additional_damage->str();
  }

  return ss.str();
}

bool Damage::serialize(ostream& stream)
{
  Dice::serialize(stream);
  Serialize::write_enum(stream, damage_type);
  Serialize::write_bool(stream, chaotic);

  if (additional_damage)
  {
    Serialize::write_class_id(stream, additional_damage->get_class_identifier());
    additional_damage->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  return true;
}

bool Damage::deserialize(istream& stream)
{
  Dice::deserialize(stream);
  Serialize::read_enum(stream, damage_type);
  Serialize::read_bool(stream, chaotic);

  ClassIdentifier ci = CLASS_ID_NULL;
  Serialize::read_class_id(stream, ci);

  if (ci != CLASS_ID_NULL)
  {
    additional_damage = std::make_shared<Damage>();
    additional_damage->deserialize(stream);
  }

  return true;
}

ClassIdentifier Damage::internal_class_identifier() const
{
  return CLASS_ID_DAMAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
