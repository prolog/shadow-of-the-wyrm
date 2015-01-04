#include "SeasonTextKeys.hpp"
#include "Summer.hpp"

using namespace std;

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

  months_in_season.insert(Months::MONTH_6);
  months_in_season.insert(Months::MONTH_7);
  months_in_season.insert(Months::MONTH_8);
}

Season Summer::get_season() const
{
  return Season::SEASON_SUMMER;
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
  return Season::SEASON_SPRING;
}

Season Summer::get_next_season() const
{
  return Season::SEASON_AUTUMN;
}

ISeason* Summer::clone()
{
  return new Summer(*this);
}

ClassIdentifier Summer::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SUMMER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Summer_test.cpp"
#endif

