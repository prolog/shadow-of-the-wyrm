#include "ItemTypes.hpp"
#include "SeasonTextKeys.hpp"
#include "Winter.hpp"

using namespace std;

Winter::Winter()
{
  initialize_months();
  initialize_foragables();
  initialize_herbs();
}

void Winter::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.insert(Months::MONTH_1);
  months_in_season.insert(Months::MONTH_2);
  months_in_season.insert(Months::MONTH_12);
}

void Winter::initialize_foragables()
{
  foragables = {{TileType::TILE_TYPE_SEA, {ItemIdKeys::ITEM_ID_KELP}}};
}

void Winter::initialize_herbs()
{
}

Season Winter::get_season() const
{
  return Season::SEASON_WINTER;
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
  return Season::SEASON_AUTUMN;
}

Season Winter::get_next_season() const
{
  return Season::SEASON_SPRING;
}

ISeason* Winter::clone()
{
  return new Winter(*this);
}

ClassIdentifier Winter::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WINTER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Winter_test.cpp"
#endif

