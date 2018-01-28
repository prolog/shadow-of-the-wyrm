#include "StartingLocation.hpp"
#include "Serialize.hpp"

using namespace std;

StartingLocation::StartingLocation()
: location({-1, -1})
{
}

StartingLocation::StartingLocation(const string& ident, const Coordinate& sloc, const string& desc_sid)
: id(ident), location(sloc), description_sid(desc_sid)
{
}

bool StartingLocation::operator==(const StartingLocation sl2) const
{
  bool result = true;

  result = result && (id == sl2.id);
  result = result && (location == sl2.location);
  result = result && (description_sid == sl2.description_sid);

  return result;
}

void StartingLocation::set_id(const string& new_id)
{
  id = new_id;
}

string StartingLocation::get_id() const
{
  return id;
}

void StartingLocation::set_location(const Coordinate& new_location)
{
  location = new_location;
}

Coordinate StartingLocation::get_location() const
{
  return location;
}

void StartingLocation::set_description_sid(const string& new_desc_sid)
{
  description_sid = new_desc_sid;
}

string StartingLocation::get_description_sid() const
{
  return description_sid;
}

bool StartingLocation::serialize(ostream& stream) const
{
  Serialize::write_string(stream, id);
  Serialize::write_int(stream, location.first);
  Serialize::write_int(stream, location.second);
  Serialize::write_string(stream, description_sid);

  return true;
}

bool StartingLocation::deserialize(istream& stream)
{
  Serialize::read_string(stream, id);
  Serialize::read_int(stream, location.first);
  Serialize::read_int(stream, location.second);
  Serialize::read_string(stream, description_sid);

  return true;
}

ClassIdentifier StartingLocation::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STARTING_LOCATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/StartingLocation_test.cpp"
#endif

