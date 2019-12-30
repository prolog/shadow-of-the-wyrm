#include "SpritesheetLocation.hpp"
#include "Serialize.hpp"

using namespace std;

// SpritesheetIndices
const string SpritesheetIndex::SPRITESHEET_INDEX_SYSTEM = "sys";

SpritesheetIndex::SpritesheetIndex()
{
}

SpritesheetIndex::~SpritesheetIndex()
{
}

// SpritesheetReference
const string SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST = "_magic_blast";
const string SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NWSE = "_beam_nwse";
const string SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NESW = "_beam_nesw";
const string SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_NS = "_beam_ns";
const string SpritesheetReference::SPRITESHEET_REFERENCE_BEAM_EW = "_beam_ew";

SpritesheetReference::SpritesheetReference()
{
}

SpritesheetReference::~SpritesheetReference()
{
}

// SpritesheetLocation
SpritesheetLocation::SpritesheetLocation()
: coord(-1, -1)
{
}

SpritesheetLocation::SpritesheetLocation(const string& new_index, const Coordinate& new_coord)
: index(new_index), coord(new_coord)
{
}

SpritesheetLocation::SpritesheetLocation(const string& new_index, const string& new_ref_id)
: index(new_index), reference_id(new_ref_id), coord(-1, -1)
{
}

bool SpritesheetLocation::operator==(const SpritesheetLocation& sl) const
{
  bool result = true;

  result = result && (index == sl.index);
  result = result && (coord == sl.coord);
  result = result && (reference_id == sl.reference_id);

  return result;
}

void SpritesheetLocation::set_index(const string& new_index)
{
  index = new_index;
}

string SpritesheetLocation::get_index() const
{
  return index;
}

void SpritesheetLocation::set_reference_id(const string& new_ref_id)
{
  reference_id = new_ref_id;
}

string SpritesheetLocation::get_reference_id() const
{
  return reference_id;
}

bool SpritesheetLocation::uses_reference_id() const
{
  return (reference_id.empty() == false);
}

void SpritesheetLocation::set_coordinate(const Coordinate& new_coord)
{
  coord = new_coord;
}

Coordinate SpritesheetLocation::get_coordinate() const
{
  return coord;
}

bool SpritesheetLocation::serialize(ostream& stream) const
{
  Serialize::write_string(stream, index);
  Serialize::write_string(stream, reference_id);
  Serialize::write_int(stream, coord.first);
  Serialize::write_int(stream, coord.second);

  return true;
}

bool SpritesheetLocation::deserialize(istream& stream)
{
  Serialize::read_string(stream, index);
  Serialize::read_string(stream, reference_id);
  Serialize::read_int(stream, coord.first);
  Serialize::read_int(stream, coord.second);

  return true;
}

ClassIdentifier SpritesheetLocation::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPRITESHEET_LOCATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpritesheetLocation_test.cpp"
#endif
