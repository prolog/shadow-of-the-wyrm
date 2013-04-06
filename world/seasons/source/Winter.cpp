#include "SeasonTextKeys.hpp"
#include "Winter.hpp"

using namespace std;

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

  months_in_season.insert(MONTH_1);
  months_in_season.insert(MONTH_2);
  months_in_season.insert(MONTH_12);
}

Season Winter::get_season() const
{
  return SEASON_WINTER;
}

string Winter::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_WINTER;
}

string Winter::get_new_season_message_sid() const
{
  return SeasonTextKeys::SEASON_TRANSITION_WINTER;
}

Season Winter::get_previous_season() const
{
  return SEASON_AUTUMN;
}

Season Winter::get_next_season() const
{
  return SEASON_SPRING;
}

ISeason* Winter::clone()
{
  return new Winter(*this);
}

ClassIdentifier Winter::internal_class_identifier() const
{
  return CLASS_ID_WINTER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Winter_test.cpp"
#endif

