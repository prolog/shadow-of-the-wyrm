#include "Calendar.hpp"

Calendar::Calendar()
: seconds(0)
{
}

void Calendar::add_seconds(const uint additional_seconds)
{
  seconds += additional_seconds;
}
