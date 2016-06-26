#include "ItemTypes.hpp"
#include "SeasonTextKeys.hpp"
#include "Summer.hpp"

using namespace std;

Summer::Summer()
{
  initialize_months();
  initialize_foragables();
  initialize_herbs();
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

void Summer::initialize_foragables()
{
  foragables = {{TileType::TILE_TYPE_SEA, {ItemIdKeys::ITEM_ID_KELP}},
                {TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_ROOT}},
                {TileType::TILE_TYPE_BUSH, {ItemIdKeys::ITEM_ID_BERRIES}}};
}

void Summer::initialize_herbs()
{
  herbs = {{TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_BLACKROOT, ItemIdKeys::ITEM_ID_VERBENA, ItemIdKeys::ITEM_ID_WHITE_BASIL}},
           {TileType::TILE_TYPE_BUSH, {ItemIdKeys::ITEM_ID_STONEFLOWER}}};
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

