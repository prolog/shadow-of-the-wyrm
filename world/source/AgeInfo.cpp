#include "AgeInfo.hpp"

AgeInfo::AgeInfo()
: starting_age(0,0), maximum_age(0,0)
{
}

AgeInfo::AgeInfo(const Range<uint>& new_starting_age, const Range<uint>& new_maximum_age)
: starting_age(new_starting_age), maximum_age(new_maximum_age)
{
}

void AgeInfo::set_starting_age(const Range<uint>& new_starting_age)
{
  starting_age = new_starting_age;
}

Range<uint> AgeInfo::get_starting_age() const
{
  return starting_age;
}

void AgeInfo::set_maximum_age(const Range<uint>& new_maximum_age)
{
  maximum_age = new_maximum_age;
}

Range<uint> AgeInfo::get_maximum_age() const
{
  return maximum_age;
}

