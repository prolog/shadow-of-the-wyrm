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

  months_in_season.insert(MONTH_6);
  months_in_season.insert(MONTH_7);
  months_in_season.insert(MONTH_8);
}

Season Summer::get_season() const
{
  return SEASON_SUMMER;
}

string Summer::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_SUMMER;
}

string Summer::get_new_season_message_sid() const
{
  return SeasonTextKeys::SEASON_TRANSITION_SUMMER;
}

Season Summer::get_previous_season() const
{
  return SEASON_SPRING;
}

Season Summer::get_next_season() const
{
  return SEASON_AUTUMN;
}

ISeason* Summer::clone()
{
  return new Summer(*this);
}

ClassIdentifier Summer::internal_class_identifier() const
{
  return CLASS_ID_SUMMER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Summer_test.cpp"
#endif

