#include <string>
#include <sstream>
#include "Conversion.hpp"
#include "Damage.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

Damage::Damage()
: Dice(0, 0, 0), damage_type(DamageType::DAMAGE_TYPE_SLASH), chaotic(false), vorpal(false), piercing(false), incorporeal(false), effect_bonus(0)
{
}

Damage::Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const vector<string>& rslays, const bool chaos, const bool vorp, const bool pierce, const bool incorp, const int eb, const StatusAilments& ailments)
: Dice(dice, sides, mod), damage_type(dtype), slays_races(rslays), chaotic(chaos), vorpal(vorp), piercing(pierce), incorporeal(incorp), effect_bonus(eb), status_ailments(ailments)
{
}

Damage::Damage(const Damage& d)
: Dice(d.num_dice, d.dice_sides, d.modifier), damage_type(d.damage_type), slays_races(d.slays_races), chaotic(d.chaotic), vorpal(d.vorpal), piercing(d.piercing), incorporeal(d.incorporeal), effect_bonus(d.effect_bonus), status_ailments(d.status_ailments)
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
    slays_races = d.slays_races;
    chaotic     = d.chaotic;
    vorpal      = d.vorpal;
    piercing    = d.piercing;
    incorporeal = d.incorporeal;
    effect_bonus= d.effect_bonus;
    status_ailments = d.status_ailments;
    
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
    match = match && (status_ailments == d.status_ailments );
    match = match && (slays_races == d.slays_races);

    // bypass the "chaotic" flag.  otherwise, unit tests fail
    // roughly 50% of the time when chaotic is on. :)
    match = match && (damage_type == d.damage_type      );

    match = match && (chaotic     == d.get_chaotic()    );
    match = match && (vorpal      == d.get_vorpal()     );
    match = match && (piercing    == d.get_piercing()   );
    match = match && (incorporeal == d.get_incorporeal());
    match = match && (effect_bonus == d.get_effect_bonus());
    
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
    return static_cast<DamageType>(RNG::range(static_cast<int>(DamageType::DAMAGE_TYPE_SLASH), static_cast<int>(DamageType::DAMAGE_TYPE_MAX)-1));
  }
}

void Damage::set_slays_races(const vector<string>& new_slays_races)
{
  slays_races = new_slays_races;
}

vector<string> Damage::get_slays_races() const
{
  vector<string> slays_combined = slays_races;

  if (additional_damage != nullptr)
  {
    vector<string> addl_slays = additional_damage->get_slays_races();
    slays_combined.insert(slays_combined.end(), addl_slays.begin(), addl_slays.end());
  }

  return slays_combined;
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

void Damage::set_vorpal(const bool new_vorpal)
{
  vorpal = new_vorpal;
}

bool Damage::get_vorpal() const
{
  return vorpal;
}

void Damage::set_piercing(const bool new_piercing)
{
  piercing = new_piercing;
}

bool Damage::get_piercing() const
{
  return piercing;
}

void Damage::set_incorporeal(const bool new_incorporeal)
{
  incorporeal = new_incorporeal;
}

bool Damage::get_incorporeal() const
{
  return incorporeal;
}

void Damage::set_effect_bonus(const int new_effect_bonus)
{
  effect_bonus = new_effect_bonus;
}

int Damage::get_effect_bonus() const
{
  return effect_bonus;
}

void Damage::set_status_ailments(const StatusAilments& new_status_ailments)
{
  status_ailments = new_status_ailments;
}

StatusAilments Damage::get_status_ailments() const
{
  return status_ailments;
}

bool Damage::is_always_zero() const
{
  return (num_dice == 0) || (dice_sides == 0);
}

bool Damage::contains(const DamageType dt) const
{
  // First check the main damage type.
  if (damage_type == dt) return true;

  // If not, check any additional damage types.
  auto add_dmg = additional_damage;

  while (add_dmg != nullptr)
  {
    if (add_dmg->get_damage_type() == dt) return true;
    else add_dmg = add_dmg->get_additional_damage();
  }

  return false;
}

string Damage::str() const
{
  ostringstream ss;
  string modifier_s;

  int modifier_abs = std::abs(modifier);
  
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
    ss << modifier_s << modifier_abs;
  }
  
  if (additional_damage)
  {
    ss << "+" << additional_damage->str();
  }

  return ss.str();
}

bool Damage::serialize(ostream& stream) const
{
  Dice::serialize(stream);
  Serialize::write_enum(stream, damage_type);
  Serialize::write_bool(stream, chaotic);
  Serialize::write_bool(stream, vorpal);
  Serialize::write_bool(stream, piercing);
  Serialize::write_bool(stream, incorporeal);
  Serialize::write_int(stream, effect_bonus);

  status_ailments.serialize(stream);
  Serialize::write_string_vector(stream, slays_races);

  if (additional_damage)
  {
    Serialize::write_class_id(stream, additional_damage->get_class_identifier());
    additional_damage->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  return true;
}

bool Damage::deserialize(istream& stream)
{
  Dice::deserialize(stream);
  Serialize::read_enum(stream, damage_type);
  Serialize::read_bool(stream, chaotic);
  Serialize::read_bool(stream, vorpal);
  Serialize::read_bool(stream, piercing);
  Serialize::read_bool(stream, incorporeal);
  Serialize::read_int(stream, effect_bonus);

  status_ailments.deserialize(stream);
  Serialize::read_string_vector(stream, slays_races);

  ClassIdentifier ci = ClassIdentifier::CLASS_ID_NULL;
  Serialize::read_class_id(stream, ci);

  if (ci != ClassIdentifier::CLASS_ID_NULL)
  {
    additional_damage = std::make_shared<Damage>();
    additional_damage->deserialize(stream);
  }

  return true;
}

ClassIdentifier Damage::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DAMAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
