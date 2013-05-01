#include "Lock.hpp"
#include "Serialize.hpp"

using namespace std;

Lock::Lock()
: locked(true) /* Locks are locked by default - makes things easier than assuming otherwise */
{
}

Lock::Lock(const string& new_lock_id, const bool new_locked_val)
: lock_id(new_lock_id), locked(new_locked_val)
{
}

bool Lock::operator==(const Lock& lock) const
{
  return true;
}

void Lock::set_lock_id(const string& new_lock_id)
{
  lock_id = new_lock_id;
}

string Lock::get_lock_id() const
{
  return lock_id;
}

void Lock::set_locked(const bool new_locked)
{
  locked = new_locked;
}

bool Lock::get_locked() const
{
  return locked;
}

bool Lock::handle()
{
  locked = !locked;

  return true;
}

bool Lock::serialize(ostream& stream)
{
  Serialize::write_string(stream, lock_id);
  Serialize::write_bool(stream, locked);

  return true;
}

bool Lock::deserialize(istream& stream)
{
  Serialize::read_string(stream, lock_id);
  Serialize::read_bool(stream, locked);
  return true;
}

ClassIdentifier Lock::internal_class_identifier() const
{
  return CLASS_ID_LOCK;
}

#ifdef UNIT_TESTS
#include "unit_tests/Lock_test.cpp"
#endif

