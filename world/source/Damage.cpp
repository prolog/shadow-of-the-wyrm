#include <string>
#include <sstream>
#include "Conversion.hpp"
#include "Damage.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

Damage::Damage()
: Dice(0, 0, 0), chaotic(false), vorpal(false), draining(false), ethereal(false), piercing(false), incorporeal(false), scything(false), explosive(false), damage_type(DamageType::DAMAGE_TYPE_SLASH), effect_bonus(0)
{
}

Damage::Damage(const uint dice, const uint sides, const int mod, const DamageType dtype, const vector<string>& rslays, const bool chaos, const bool vorp, const bool drain, const bool ether, const bool pierce, const bool incorp, const bool scy, const bool exp, const int eb, const StatusAilments& ailments)
: Dice(dice, sides, mod), chaotic(chaos), vorpal(vorp), draining(drain), ethereal(ether), piercing(pierce), incorporeal(incorp), scything(scy), explosive(exp), damage_type(dtype), slays_races(rslays), effect_bonus(eb), status_ailments(ailments)
{
}

Damage::Damage(const Damage& d)
: Dice(d.num_dice, d.dice_sides, d.modifier), chaotic(d.chaotic), vorpal(d.vorpal), draining(d.draining), ethereal(d.ethereal),  piercing(d.piercing), incorporeal(d.incorporeal), scything(d.scything), explosive(d.explosive), damage_type(d.damage_type), slays_races(d.slays_races), effect_bonus(d.effect_bonus), status_ailments(d.status_ailments)
{
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
    draining    = d.draining;
    ethereal    = d.ethereal;
    piercing    = d.piercing;
    incorporeal = d.incorporeal;
    scything    = d.scything;
    explosive   = d.explosive;
    effect_bonus= d.effect_bonus;
    status_ailments = d.status_ailments;    
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
    match = match && (draining    == d.get_draining()   );
    match = match && (ethereal    == d.get_ethereal()   );
    match = match && (piercing    == d.get_piercing()   );
    match = match && (incorporeal == d.get_incorporeal());
    match = match && (scything    == d.get_scything()   );
    match = match && (explosive   == d.get_explosive()  );
    match = match && (effect_bonus == d.get_effect_bonus());
    
    return match;
  }
  
  return false;
}

Damage::~Damage()
{
}

vector<DamageType> Damage::get_all_damage_types()
{
  return { DamageType::DAMAGE_TYPE_SLASH, DamageType::DAMAGE_TYPE_PIERCE, DamageType::DAMAGE_TYPE_POUND, DamageType::DAMAGE_TYPE_HEAT, DamageType::DAMAGE_TYPE_COLD, DamageType::DAMAGE_TYPE_ACID, DamageType::DAMAGE_TYPE_POISON, DamageType::DAMAGE_TYPE_HOLY, DamageType::DAMAGE_TYPE_SHADOW, DamageType::DAMAGE_TYPE_ARCANE, DamageType::DAMAGE_TYPE_LIGHTNING };
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

// damage category checks use the base damage type and ignore the chaotic flag
DamageCategory Damage::get_damage_category() const
{
  DamageCategory category = DamageCategory::DAMAGE_CATEGORY_OTHER;

  if (damage_type == DamageType::DAMAGE_TYPE_SLASH || damage_type == DamageType::DAMAGE_TYPE_PIERCE || damage_type == DamageType::DAMAGE_TYPE_POUND)
  {
    category = DamageCategory::DAMAGE_CATEGORY_PHYSICAL;
  }

  return category;
}

void Damage::set_slays_races(const vector<string>& new_slays_races)
{
  slays_races = new_slays_races;
}

vector<string> Damage::get_slays_races() const
{
  return slays_races;
}

void Damage::set_damage_flags(const map<DamageFlagType, bool>& dflags)
{
  for (const auto& dpair : dflags)
  {
    set_damage_flag(dpair.first, dpair.second);
  }
}

void Damage::set_damage_flag(const DamageFlagType df, const bool value)
{
  static_assert(DamageFlagType::DAMAGE_FLAG_LAST == DamageFlagType(7), "Unexpected DamageFlag::DAMAGE_FLAG_LAST");

  switch (df)
  {
    case DamageFlagType::DAMAGE_FLAG_CHAOTIC:
      chaotic = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_VORPAL:
      vorpal = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_DRAINING:
      draining = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_ETHEREAL:
      ethereal = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_PIERCING:
      piercing = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_INCORPOREAL:
      incorporeal = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_SCYTHING:
      scything = value;
      break;
    case DamageFlagType::DAMAGE_FLAG_EXPLOSIVE:
      explosive = value;
      break;
    default:
      break;
  }
}

bool Damage::get_damage_flag(const DamageFlagType df) const
{
  bool flag = false;

  switch (df)
  {
    case DamageFlagType::DAMAGE_FLAG_CHAOTIC:
      flag = chaotic;
      break;
    case DamageFlagType::DAMAGE_FLAG_VORPAL:
      flag = vorpal;
      break;
    case DamageFlagType::DAMAGE_FLAG_DRAINING:
      flag = draining;
      break;
    case DamageFlagType::DAMAGE_FLAG_ETHEREAL:
      flag = ethereal;
      break;
    case DamageFlagType::DAMAGE_FLAG_PIERCING:
      flag = piercing;
      break;
    case DamageFlagType::DAMAGE_FLAG_INCORPOREAL:
      flag = incorporeal;
      break;
    case DamageFlagType::DAMAGE_FLAG_SCYTHING:
      flag = scything;
      break;
    case DamageFlagType::DAMAGE_FLAG_EXPLOSIVE:
      flag = explosive;
      break;
    default:
      break;
  }

  return flag;
}

vector<DamageFlagType> Damage::get_damage_flags_by_value(const bool value) const
{
  static_assert(DamageFlagType::DAMAGE_FLAG_LAST == DamageFlagType(7), "Unexpected DamageFlag::DAMAGE_FLAG_LAST");
  vector<DamageFlagType> damage_flags;

  if (chaotic == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_CHAOTIC);
  }

  if (vorpal == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_VORPAL);
  }

  if (draining == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_DRAINING);
  }

  if (ethereal == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_ETHEREAL);
  }

  if (piercing == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_PIERCING);
  }

  if (incorporeal == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_INCORPOREAL);
  }

  if (scything == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_SCYTHING);
  }

  if (explosive == value)
  {
    damage_flags.push_back(DamageFlagType::DAMAGE_FLAG_EXPLOSIVE);
  }

  return damage_flags;
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

void Damage::set_draining(const bool new_draining)
{
  draining = new_draining;
}

bool Damage::get_draining() const
{
  return draining;
}

void Damage::set_ethereal(const bool new_ethereal)
{
  ethereal = new_ethereal;
}

bool Damage::get_ethereal() const
{
  return ethereal;
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

void Damage::set_scything(const bool new_scything)
{
  scything = new_scything;
}

bool Damage::get_scything() const
{
  return scything;
}

void Damage::set_explosive(const bool new_explosive)
{
  explosive = new_explosive;
}

bool Damage::get_explosive() const
{
  return explosive;
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
  
  return ss.str();
}

bool Damage::serialize(ostream& stream) const
{
  Dice::serialize(stream);
  Serialize::write_enum(stream, damage_type);
  Serialize::write_bool(stream, chaotic);
  Serialize::write_bool(stream, vorpal);
  Serialize::write_bool(stream, draining);
  Serialize::write_bool(stream, ethereal);
  Serialize::write_bool(stream, piercing);
  Serialize::write_bool(stream, incorporeal);
  Serialize::write_bool(stream, scything);
  Serialize::write_bool(stream, explosive);
  Serialize::write_int(stream, effect_bonus);

  status_ailments.serialize(stream);
  Serialize::write_string_vector(stream, slays_races);

  return true;
}

bool Damage::deserialize(istream& stream)
{
  Dice::deserialize(stream);
  Serialize::read_enum(stream, damage_type);
  Serialize::read_bool(stream, chaotic);
  Serialize::read_bool(stream, vorpal);
  Serialize::read_bool(stream, draining);
  Serialize::read_bool(stream, ethereal);
  Serialize::read_bool(stream, piercing);
  Serialize::read_bool(stream, incorporeal);
  Serialize::read_bool(stream, scything);
  Serialize::read_bool(stream, explosive);
  Serialize::read_int(stream, effect_bonus);

  status_ailments.deserialize(stream);
  Serialize::read_string_vector(stream, slays_races);

  return true;
}

ClassIdentifier Damage::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DAMAGE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
