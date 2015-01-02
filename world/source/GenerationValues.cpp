#include "GenerationValues.hpp"
#include "Serialize.hpp"

using namespace std;

GenerationValues::GenerationValues()
: current(0),
maximum(-1),
rarity(RARITY_COMMON), 
danger_level(0)
{
}

GenerationValues::~GenerationValues()
{
}

bool GenerationValues::operator==(const GenerationValues& gv) const
{
  bool result = true;

  result = result && (current == gv.current);
  result = result && (maximum == gv.maximum);
  result = result && (rarity == gv.rarity);
  result = result && (danger_level == gv.danger_level);

  return result;
}

void GenerationValues::set_current(const int new_current)
{
  current = new_current;
}

int GenerationValues::incr_current()
{
  return ++current;
}

int GenerationValues::get_current() const
{
  return current;
}

void GenerationValues::set_maximum(const int new_maximum)
{
  maximum = new_maximum;
}

int GenerationValues::get_maximum() const
{
  return maximum;
}

// Check to see if the maximum number of generatable creatures has been
// reached.
bool GenerationValues::is_maximum_reached() const
{
  return (current == maximum);
}

void GenerationValues::set_danger_level(const int new_danger_level)
{
  danger_level = new_danger_level;
}

int GenerationValues::get_danger_level() const
{
  return danger_level;
}

void GenerationValues::set_rarity(const Rarity new_rarity)
{
  rarity = new_rarity;
}

Rarity GenerationValues::get_rarity() const
{
  return rarity;
}

bool GenerationValues::serialize(ostream& stream) const
{
  Serialize::write_int(stream, current);
  Serialize::write_int(stream, maximum);
  Serialize::write_enum(stream, rarity);
  Serialize::write_uint(stream, danger_level);

  return true;
}

bool GenerationValues::deserialize(istream& stream)
{
  Serialize::read_int(stream, current);
  Serialize::read_int(stream, maximum);
  Serialize::read_enum(stream, rarity);
  Serialize::read_enum(stream, danger_level);

  return true;
}

ClassIdentifier GenerationValues::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GENERATION_VALUES;
}