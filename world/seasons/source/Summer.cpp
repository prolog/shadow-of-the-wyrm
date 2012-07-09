#include "Summer.hpp"
#include "StringConstants.hpp"

using std::string;

Summer::Summer()
{
  initialize_months();
}

void Summer::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.push_back(MONTH_6);
  months_in_season.push_back(MONTH_7);
  months_in_season.push_back(MONTH_8);
}

Season Summer::get_season() const
{
  return SEASON_SUMMER;
}

string Summer::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_SUMMER;
}

Season Summer::get_previous_season() const
{
  return SEASON_SPRING;
}

Season Summer::get_next_season() const
{
  return SEASON_AUTUMN;
}
