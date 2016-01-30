#include "SeedCalculator.hpp"
#include "Calendar.hpp"

double SeedCalculator::calculate_sprouting_seconds(const Date& date)
{
  Date sprouting_date(date.get_seconds(), date.get_minutes(), date.get_hours(), 1, 1, date.get_day_of_year(), static_cast<int>(Months::MONTH_5), date.get_year() + 1);
  Calendar c;

  return c.get_seconds_from_date(sprouting_date);
}

