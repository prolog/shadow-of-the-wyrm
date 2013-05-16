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

const int WandConstants::MIN_CHARGES = 2;
const int WandConstants::MAX_CHARGES = 6;

Wand::Wand()
{
  type = ITEM_TYPE_WAND;
  symbol ='\\';
  range = 0;
  shape = SPELL_SHAPE_BEAM;
  charges = 0;
}

Wand::~Wand()
{
}

bool Wand::operator==(const Wand& rhs) const
{
  bool result = Item::operator==(rhs);

  result = result && (range == rhs.range);
  result = result && (shape == rhs.shape);
  result = result && (charges == rhs.charges);

  return result;
}

void Wand::set_range(const uint new_range)
{
  range = new_range;
}

uint Wand::get_range() const
{
  return range;
}

void Wand::set_spell_shape_type(const SpellShapeType new_shape)
{
  shape = new_shape;
}

SpellShapeType Wand::get_spell_shape_type() const
{
  return shape;
}

void Wand::reset_charges()
{
  charges = RNG::range(WandConstants::MIN_CHARGES, WandConstants::MAX_CHARGES);
}

void Wand::set_charges(const uint new_charges)
{
  charges = new_charges;
}

uint Wand::get_charges() const
{
  return charges;
}

Item* Wand::clone()
{
  Wand* new_wand = new Wand(*this);

  reset_charges();

  return new_wand;
}

bool Wand::serialize(ostream& stream)
{
  Item::serialize(stream);

  Serialize::write_uint(stream, range);
  Serialize::write_enum(stream, shape);
  Serialize::write_uint(stream, charges);

  return true;
}

bool Wand::deserialize(istream& stream)
{
  Item::deserialize(stream);

  Serialize::read_uint(stream, range);
  Serialize::read_enum(stream, shape);
  Serialize::read_uint(stream, charges);

  return true;
}

ClassIdentifier Wand::internal_class_identifier() const
{
  return CLASS_ID_WAND;
}

#ifdef UNIT_TESTS
#include "unit_tests/Wand_test.cpp"
#endif

