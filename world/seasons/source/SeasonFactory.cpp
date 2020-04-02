#include "SeasonFactory.hpp"
#include "Spring.hpp"
#include "Summer.hpp"
#include "Autumn.hpp"
#include "Winter.hpp"

using namespace std;

SeasonSerializationMap SeasonFactory::season_map;

SeasonFactory::SeasonFactory()
{
}

SeasonFactory::~SeasonFactory()
{
}

ISeasonPtr SeasonFactory::create_season(const Season season)
{
  ISeasonPtr new_season;

  switch(season)
  {
    case Season::SEASON_SPRING:
      new_season = std::make_unique<Spring>();
      break;
    case Season::SEASON_SUMMER:
      new_season = std::make_unique<Summer>();
      break;
    case Season::SEASON_AUTUMN:
      new_season = std::make_unique<Autumn>();
      break;
    case Season::SEASON_WINTER:
    default:
      new_season = std::make_unique<Winter>();
      break;
  }

  return new_season;
}

ISeasonPtr SeasonFactory::create_season(const ClassIdentifier ci)
{
  ISeasonPtr season;

  if (season_map.empty())
  {
    initialize_season_map();
  }

  SeasonSerializationMap::iterator s_it = season_map.find(ci);

  if (s_it != season_map.end())
  {
    season = ISeasonPtr(s_it->second->clone());
  }

  return season;
}

ISeasonPtr SeasonFactory::create_season(const uint month_of_year)
{
  ISeasonPtr season;
  set<Season> seasons = {Season::SEASON_SPRING, Season::SEASON_SUMMER, Season::SEASON_AUTUMN, Season::SEASON_WINTER};

  for (Season cur_season_enum : seasons)
  {
    ISeasonPtr cur_season = create_season(cur_season_enum);
    set<Months> months = cur_season->get_months_in_season();

    if (months.find(static_cast<Months>(month_of_year)) != months.end())
    {
      season = ISeasonPtr(cur_season->clone());
      break;
    }
  }

  return season;
}

void SeasonFactory::initialize_season_map()
{
  season_map.clear();

  ISeasonPtr spring = std::make_unique<Spring>();
  ISeasonPtr summer = std::make_unique<Summer>();
  ISeasonPtr autumn = std::make_unique<Autumn>();
  ISeasonPtr winter = std::make_unique<Winter>();

  season_map.insert(make_pair(ClassIdentifier::CLASS_ID_SPRING, std::move(spring)));
  season_map.insert(make_pair(ClassIdentifier::CLASS_ID_SUMMER, std::move(summer)));
  season_map.insert(make_pair(ClassIdentifier::CLASS_ID_AUTUMN, std::move(autumn)));
  season_map.insert(make_pair(ClassIdentifier::CLASS_ID_WINTER, std::move(winter)));
}