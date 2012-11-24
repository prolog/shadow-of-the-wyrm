#include <limits>
#include "DeityStatus.hpp"
#include "Serialize.hpp"

using namespace std;

DeityStatus::DeityStatus()
: piety(100), crowned(false)
{
}

DeityStatus::~DeityStatus()
{
}

bool DeityStatus::operator==(const DeityStatus& status)
{
  bool result = true;

  result = result && (piety == status.piety);
  result = result && (crowned == status.crowned);

  return result;
}

void DeityStatus::set_piety(const int new_piety)
{
  piety = new_piety;
}

int DeityStatus::get_piety() const
{
  return piety;
}

// Increment piety, guarding against ADOMish overflow.
void DeityStatus::increment_piety(const int inc_amount)
{
  long new_piety = piety + inc_amount;
  
  if (new_piety <= numeric_limits<int>::max())
  {
    piety = new_piety;
  }
  else
  {
    piety = numeric_limits<int>::max();
  }
}

// Decrement piety, guarding against ADOMish overflow.
void DeityStatus::decrement_piety(const int dec_amount)
{
  long new_piety = piety - dec_amount;

  if (new_piety >= numeric_limits<int>::min())
  {
    piety = new_piety;
  }
  else
  {
    piety = numeric_limits<int>::min();
  }
}

// Set/get whether the creature is a champion of the deity, and has been crowned.
void DeityStatus::set_crowned(const bool new_crowned_status)
{
  crowned = new_crowned_status;
}

bool DeityStatus::get_crowned() const
{
  return crowned;
}

bool DeityStatus::serialize(ostream& stream)
{
  Serialize::write_int(stream, piety);
  Serialize::write_bool(stream, crowned);

  return true;
}

bool DeityStatus::deserialize(istream& stream)
{
  Serialize::read_int(stream, piety);
  Serialize::read_bool(stream, crowned);

  return true;
}

ClassIdentifier DeityStatus::internal_class_identifier() const
{
  return CLASS_ID_DEITY_STATUS;
}

#ifdef UNIT_TESTS
#include "unit_tests/DeityStatus_test.cpp"
#endif


