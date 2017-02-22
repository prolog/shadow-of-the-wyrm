#include "Status.hpp"
#include "Serialize.hpp"

using namespace std;

Status::Status()
: value(false), danger_level(1)
{
}

Status::Status(const string& new_id, const bool new_value, const int new_danger_level, const string& new_source_id)
: id(new_id), value(new_value), danger_level(new_danger_level), source_id(new_source_id)
{
}

bool Status::operator==(const Status& s) const
{
  bool result = true;

  result = result && (id == s.id);
  result = result && (value == s.value);
  result = result && (danger_level == s.danger_level);
  result = result && (source_id == s.source_id);

  return result;
}

void Status::set_id(const string& new_id)
{
  id = new_id;
}

string Status::get_id() const
{
  return id;
}

void Status::set_value(const bool new_value)
{
  value = new_value;
}

bool Status::get_value() const
{
  return value;
}

void Status::set_danger_level(const int new_danger_level)
{
  danger_level = new_danger_level;
}

int Status::get_danger_level() const
{
  return danger_level;
}

void Status::set_source_id(const string& new_source_id)
{
  source_id = new_source_id;
}

string Status::get_source_id() const
{
  return source_id;
}

bool Status::serialize(ostream& stream) const
{
  Serialize::write_string(stream, id);
  Serialize::write_bool(stream, value);
  Serialize::write_int(stream, danger_level);
  Serialize::write_string(stream, source_id);

  return true;
}

bool Status::deserialize(istream& stream)
{
  Serialize::read_string(stream, id);
  Serialize::read_bool(stream, value);
  Serialize::read_int(stream, danger_level);
  Serialize::read_string(stream, source_id);
  
  return true;
}

ClassIdentifier Status::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_STATUS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Status_test.cpp"
#endif
