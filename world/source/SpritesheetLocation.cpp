#include "SpritesheetLocation.hpp"
#include "Serialize.hpp"

using namespace std;

SpritesheetLocation::SpritesheetLocation()
: row(-1), col(-1)
{
}

SpritesheetLocation::SpritesheetLocation(const string& new_index, const int new_row, const int new_col)
: index(new_index), row(new_row), col(new_col)
{
}

bool SpritesheetLocation::operator==(const SpritesheetLocation& sl) const
{
  bool result = true;

  result = result && (index == sl.index);
  result = result && (row == sl.row);
  result = result && (col == sl.col);

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

void SpritesheetLocation::set_row(const int new_row)
{
  row = new_row;
}

int SpritesheetLocation::get_row() const
{
  return row;
}

void SpritesheetLocation::set_col(const int new_col)
{
  col = new_col;
}

int SpritesheetLocation::get_col() const
{
  return col;
}

bool SpritesheetLocation::serialize(ostream& stream) const
{
  Serialize::write_string(stream, index);
  Serialize::write_int(stream, row);
  Serialize::write_int(stream, col);

  return true;
}

bool SpritesheetLocation::deserialize(istream& stream)
{
  Serialize::read_string(stream, index);
  Serialize::read_int(stream, row);
  Serialize::read_int(stream, col);

  return true;
}

ClassIdentifier SpritesheetLocation::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPRITESHEET_LOCATION;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpritesheetLocation_test.cpp"
#endif
