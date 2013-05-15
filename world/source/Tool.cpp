#include "Tool.hpp"
#include "Serialize.hpp"

using namespace std;

Tool::Tool()
{
  type = ITEM_TYPE_TOOL;
  symbol = '(';
}

Tool::~Tool()
{
}

bool Tool::operator==(const Tool& rhs) const
{
  bool result = Item::operator==(rhs);

  result = result && (lock_id == rhs.lock_id);

  return result;
}

void Tool::set_lock_id(const string& new_lock_id)
{
  lock_id = new_lock_id;
}

string Tool::get_lock_id() const
{
  return lock_id;
}

Item* Tool::clone()
{
  return new Tool(*this);
}

ClassIdentifier Tool::internal_class_identifier() const
{
  return CLASS_ID_TOOL;
}

bool Tool::serialize(ostream& stream)
{
  Item::serialize(stream);
  
  Serialize::write_string(stream, lock_id);

  return true;
}

bool Tool::deserialize(istream& stream)
{
  Item::deserialize(stream);

  Serialize::read_string(stream, lock_id);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Tool_test.cpp"
#endif

