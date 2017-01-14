#include <algorithm>
#include <sstream>
#include "Wand.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"

using namespace std;

// Only ever referenced by Wand's internals, so kept in the CPP file for now.
class WandConstants
{
  public:
    static const int MIN_CHARGES;
    static const int MAX_CHARGES;
};

const int WandConstants::MIN_CHARGES = 3;
const int WandConstants::MAX_CHARGES = 7;

Wand::Wand()
{
  type = ItemType::ITEM_TYPE_WAND;
  symbol ='\\';
  range = 0;
  radius = 1;
  shape = SpellShapeType::SPELL_SHAPE_BEAM;
  has_damage = false;
  spell_colour = Colour::COLOUR_WHITE;
  
  set_initial_charges();
}

Wand::~Wand()
{
}

bool Wand::operator==(const Wand& rhs) const
{
  bool result = Item::operator==(rhs);

  result = result && wand_properties_match(rhs);

  return result;
}

bool Wand::additional_item_attributes_match(ItemPtr item) const
{
  bool attributes_match = true;

  WandPtr item_as_wand = dynamic_pointer_cast<Wand>(item);
  if (item_as_wand)
  {
    attributes_match = wand_properties_match(*item_as_wand);
  }
  else
  {
    attributes_match = false;
  }

  return attributes_match;
}

bool Wand::wand_properties_match(const Wand& rhs) const
{
  bool result = true;

  result = result && (range == rhs.range);
  result = result && (radius == rhs.radius);
  result = result && (shape == rhs.shape);
  result = result && (has_damage == rhs.has_damage);
  result = result && (damage == rhs.damage);
  result = result && (charges == rhs.charges);
  result = result && (spell_colour == rhs.spell_colour);

  return result;
}

string Wand::get_synopsis() const
{
  ostringstream oss;

  oss << "(" << charges.get_current() << ")";

  return oss.str();
}

void Wand::set_range(const uint new_range)
{
  range = new_range;
}

uint Wand::get_range() const
{
  if (charges.get_current() > 0)
  {
    return range;
  }
  else
  {
    return 0;
  }
}

void Wand::set_radius(const uint new_radius)
{
  radius = new_radius;
}

uint Wand::get_radius() const
{
  return radius;
}

void Wand::set_spell_shape_type(const SpellShapeType new_shape)
{
  shape = new_shape;
}

SpellShapeType Wand::get_spell_shape_type() const
{
  return shape;
}

void Wand::set_has_damage(const bool new_has_damage)
{
  has_damage = new_has_damage;
}

bool Wand::get_has_damage() const
{
  if (charges.get_current() > 0)
  {
    return has_damage;
  }
  else
  {
    return false;
  }
}

void Wand::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Wand::get_damage() const
{
  return damage;
}

void Wand::set_initial_charges()
{
  charges = RNG::range(WandConstants::MIN_CHARGES, WandConstants::MAX_CHARGES);
}

void Wand::set_charges(const Statistic& new_charges)
{
  if (charges.get_base() >= 0)
  {
    charges = new_charges;
  }
}

Statistic Wand::get_charges() const
{
  return charges;
}

EffectType Wand::get_effect_type() const
{
  if (charges.get_current() > 0)
  {
    return effect;
  }
  else
  {
    return EffectType::EFFECT_TYPE_NULL;
  }
}

void Wand::set_spell_colour(const Colour new_colour)
{
  spell_colour = new_colour;
}

Colour Wand::get_spell_colour() const
{
  return spell_colour;
}

// Using enchantment on a wand restores its charges and adds more
void Wand::do_enchant_item(const int points)
{
  if (RNG::percent_chance(50))
  {
    Item::do_enchant_item(points);
  }

  // Always get at least one additional charge.
  int additional_charges = std::min<int>(points / 2, 1);
  set_charges(charges.get_base() + additional_charges);
}

// In most cases, create and clone do the same thing.  But for wands, creating
// a new wand off the template also randomizes the charges.
Item* Wand::create()
{
  Item* new_wand = clone();

  set_initial_charges();

  return new_wand;
}

// Create an exact clone of this wand.
Item* Wand::clone()
{
  Wand* new_wand = new Wand(*this);

  return new_wand;
}

bool Wand::serialize(ostream& stream) const
{
  Item::serialize(stream);

  Serialize::write_uint(stream, range);
  Serialize::write_uint(stream, radius);
  Serialize::write_enum(stream, shape);
  Serialize::write_bool(stream, has_damage);
  
  damage.serialize(stream);  
  charges.serialize(stream);

  Serialize::write_enum(stream, spell_colour);

  return true;
}

bool Wand::deserialize(istream& stream)
{
  Item::deserialize(stream);

  Serialize::read_uint(stream, range);
  Serialize::read_uint(stream, radius);
  Serialize::read_enum(stream, shape);
  Serialize::read_bool(stream, has_damage);

  damage.deserialize(stream);
  charges.deserialize(stream);

  Serialize::read_enum(stream, spell_colour);

  return true;
}

ClassIdentifier Wand::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WAND;
}

#ifdef UNIT_TESTS
#include "unit_tests/Wand_test.cpp"
#endif

