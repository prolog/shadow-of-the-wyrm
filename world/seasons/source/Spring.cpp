#include "ItemTypes.hpp"
#include "SeasonTextKeys.hpp"
#include "Spring.hpp"

using namespace std;

Spring::Spring()
{
  initialize_months();
  initialize_foragables();
  initialize_herbs();
}

void Spring::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.insert(Months::MONTH_3);
  months_in_season.insert(Months::MONTH_4);
  months_in_season.insert(Months::MONTH_5);
}

void Spring::initialize_foragables()
{
  foragables = {{TileType::TILE_TYPE_SEA, {ItemIdKeys::ITEM_ID_KELP}},
                {TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_ROOT, ItemIdKeys::ITEM_ID_FIDDLEHEAD_GREEN}}};
}

void Spring::initialize_herbs()
{
  herbs = {{TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_BLACKROOT, ItemIdKeys::ITEM_ID_VERBENA, ItemIdKeys::ITEM_ID_WHITE_BASIL}},
           {TileType::TILE_TYPE_BUSH, {ItemIdKeys::ITEM_ID_STONEFLOWER, ItemIdKeys::ITEM_ID_VOXFLOWER}}};
}

Season Spring::get_season() const
{
  return Season::SEASON_SPRING;
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
  return Season::SEASON_WINTER;
}

Season Spring::get_next_season() const
{
  return Season::SEASON_SUMMER;
}

ISeason* Spring::clone()
{
  return new Spring(*this);
}

ClassIdentifier Spring::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPRING;
}

#ifdef UNIT_TESTS
#include "unit_tests/Spring_test.cpp"
#endif

