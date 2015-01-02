#include "Autumn.hpp"
#include "SeasonTextKeys.hpp"

using namespace std;

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

  months_in_season.insert(MONTH_9);
  months_in_season.insert(MONTH_10);
  months_in_season.insert(MONTH_11);
}

Season Autumn::get_season() const
{
  return SEASON_AUTUMN;
}

string Autumn::get_description_sid() const
{
  return SeasonTextKeys::SEASON_TEXT_AUTUMN;
}

string Autumn::get_new_season_message_sid() const
{
  return SeasonTextKeys::SEASON_TRANSITION_AUTUMN;
}

Season Autumn::get_previous_season() const
{
  return SEASON_SUMMER;
}

Season Autumn::get_next_season() const
{
  return SEASON_WINTER;
}

ISeason* Autumn::clone()
{
  return new Autumn(*this);
}

ClassIdentifier Autumn::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AUTUMN;
}

#ifdef UNIT_TESTS
#include "unit_tests/Autumn_test.cpp"
#endif

