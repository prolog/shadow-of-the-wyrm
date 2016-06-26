#include "Autumn.hpp"
#include "SeasonTextKeys.hpp"
#include "ItemTypes.hpp"

using namespace std;

Autumn::Autumn()
{
  initialize_months();
  initialize_foragables();
  initialize_herbs();
}

void Autumn::initialize_months()
{
  if (!months_in_season.empty())
  {
    months_in_season.clear();
  }

  months_in_season.insert(Months::MONTH_9);
  months_in_season.insert(Months::MONTH_10);
  months_in_season.insert(Months::MONTH_11);
}

void Autumn::initialize_foragables()
{
  foragables = {{TileType::TILE_TYPE_SEA, {ItemIdKeys::ITEM_ID_KELP}},
                {TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_ROOT}},
                {TileType::TILE_TYPE_BUSH, {ItemIdKeys::ITEM_ID_BERRIES}}};
}
 
void Autumn::initialize_herbs()
{
  herbs = {{TileType::TILE_TYPE_FIELD, {ItemIdKeys::ITEM_ID_BLACKROOT, ItemIdKeys::ITEM_ID_VERBENA}}};
}

Season Autumn::get_season() const
{
  return Season::SEASON_AUTUMN;
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
  return Season::SEASON_SUMMER;
}

Season Autumn::get_next_season() const
{
  return Season::SEASON_WINTER;
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

