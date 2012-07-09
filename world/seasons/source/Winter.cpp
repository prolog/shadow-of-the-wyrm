#include "Winter.hpp"
#include "StringConstants.hpp"

using std::string;

Winter::Winter()
{
  initialize_months();
}

void Winter::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.push_back(MONTH_1);
  months_in_season.push_back(MONTH_2);
  months_in_season.push_back(MONTH_12);
}

Season Winter::get_season() const
{
  return SEASON_WINTER;
}

string Winter::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_WINTER;
}

Season Winter::get_previous_season() const
{
  return SEASON_AUTUMN;
}

Season Winter::get_next_season() const
{
  return SEASON_SPRING;
}

