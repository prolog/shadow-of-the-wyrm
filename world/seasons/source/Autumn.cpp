#include "Autumn.hpp"
#include "StringConstants.hpp"

using std::string;

Autumn::Autumn()
{
  initialize_months();
}

void Autumn::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.push_back(MONTH_9);
  months_in_season.push_back(MONTH_10);
  months_in_season.push_back(MONTH_11);
}

Season Autumn::get_season() const
{
  return SEASON_AUTUMN;
}

string Autumn::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_AUTUMN;
}

Season Autumn::get_previous_season() const
{
  return SEASON_SUMMER;
}

Season Autumn::get_next_season() const
{
  return SEASON_WINTER;
}

