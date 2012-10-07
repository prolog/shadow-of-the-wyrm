#include "Spring.hpp"
#include "StringConstants.hpp"

using std::string;

Spring::Spring()
{
  initialize_months();
}

void Spring::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.insert(MONTH_3);
  months_in_season.insert(MONTH_4);
  months_in_season.insert(MONTH_5);
}

Season Spring::get_season() const
{
  return SEASON_SPRING;
}

string Spring::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_SPRING;
}

string Spring::get_new_season_message_sid() const
{
  return SeasonTextKeys::SEASON_TRANSITION_SPRING;
}

Season Spring::get_previous_season() const
{
  return SEASON_WINTER;
}

Season Spring::get_next_season() const
{
  return SEASON_SUMMER;
}

ISeason* Spring::clone()
{
  return new Spring(*this);
}

ClassIdentifier Spring::internal_class_identifier() const
{
  return CLASS_ID_SPRING;
}