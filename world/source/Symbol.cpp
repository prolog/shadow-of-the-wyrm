#include "Symbol.hpp"
#include "Serialize.hpp"

using namespace std;

Symbol::Symbol()
: symbol('?'), colour(Colour::COLOUR_WHITE)
{
}

Symbol::Symbol(const uchar new_symbol, const Colour new_colour)
: symbol(new_symbol), colour(new_colour)
{
}

Symbol::Symbol(const uchar new_symbol, const Colour new_colour, const SpritesheetLocation& new_spritesheet_location)
: symbol(new_symbol), colour(new_colour), spritesheet_location(new_spritesheet_location)
{
}

void Symbol::set_symbol(const uchar new_symbol)
{
  symbol = new_symbol;
}

uchar Symbol::get_symbol() const
{
  return symbol;
}

void Symbol::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Symbol::get_colour() const
{
  return colour;
}

bool Symbol::get_uses_spritesheet() const
{
  return (spritesheet_location.get_index().empty() == false);
}

void Symbol::set_spritesheet_location(const SpritesheetLocation& new_spritesheet_location)
{
  spritesheet_location = new_spritesheet_location;
}

SpritesheetLocation Symbol::get_spritesheet_location() const
{
  return spritesheet_location;
}

SpritesheetLocation& Symbol::get_spritesheet_location_ref()
{
  return spritesheet_location;
}

bool Symbol::operator==(const Symbol& s) const
{
  bool result = true;

  result = result && (symbol == s.symbol);
  result = result && (colour == s.colour);
  result = result && (spritesheet_location == s.spritesheet_location);

  return result;
}

bool Symbol::serialize(ostream& stream) const
{
  Serialize::write_uchar(stream, symbol);
  Serialize::write_enum(stream, colour);
  spritesheet_location.serialize(stream);

  return true;
}

bool Symbol::deserialize(istream& stream)
{
  Serialize::read_uchar(stream, symbol);
  Serialize::read_enum(stream, colour);
  spritesheet_location.deserialize(stream);

  return true;
}

ClassIdentifier Symbol::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SYMBOL;
}

#ifdef UNIT_TESTS
#include "unit_tests/Symbol_test.cpp"
#endif