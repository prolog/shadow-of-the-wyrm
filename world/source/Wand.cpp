#include "Wand.hpp"
#include "Serialize.hpp"

using namespace std;

Wand::Wand()
{
  type = ITEM_TYPE_WAND;
  symbol ='\\';
  range = 0;
  shape = SPELL_SHAPE_BEAM;
}

Wand::~Wand()
{
}

bool Wand::operator==(const Wand& rhs) const
{
  bool result = Item::operator==(rhs);

  result = result && (range == rhs.range);
  result = result && (shape == rhs.shape);

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

Item* Wand::clone()
{
  return new Wand(*this);
}

bool Wand::serialize(ostream& stream)
{
  Item::serialize(stream);

  Serialize::write_uint(stream, range);
  Serialize::write_enum(stream, shape);

  return true;
}

bool Wand::deserialize(istream& stream)
{
  Item::deserialize(stream);

  Serialize::read_uint(stream, range);
  Serialize::read_enum(stream, shape);

  return true;
}

ClassIdentifier Wand::internal_class_identifier() const
{
  return CLASS_ID_WAND;
}

#ifdef UNIT_TESTS
#include "unit_tests/Wand_test.cpp"
#endif

