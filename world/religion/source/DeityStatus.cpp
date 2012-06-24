#include <limits>
#include "DeityStatus.hpp"

using std::numeric_limits;

DeityStatus::DeityStatus()
: piety(0)
{
}

DeityStatus::~DeityStatus()
{
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
