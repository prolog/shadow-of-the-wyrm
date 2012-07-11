#include "ISeason.hpp"

std::set<Months> ISeason::get_months_in_season() const
{
  return months_in_season;
}
