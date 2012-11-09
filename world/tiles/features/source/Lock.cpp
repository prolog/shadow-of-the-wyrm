#include "Lock.hpp"

using namespace std;

bool Lock::serialize(ostream& stream)
{
  return true;
}

bool Lock::deserialize(istream& stream)
{
  return true;
}

ClassIdentifier Lock::internal_class_identifier() const
{
  return CLASS_ID_LOCK;
}

#ifdef UNIT_TESTS
#include "unit_tests/Lock_test.cpp"
#endif

