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
    case SEASON_SPRING:
      new_season = std::make_shared<Spring>();
      break;
    case SEASON_SUMMER:
      new_season = std::make_shared<Summer>();
      break;
    case SEASON_AUTUMN:
      new_season = std::make_shared<Autumn>();
      break;
    case SEASON_WINTER:
    default:
      new_season = std::make_shared<Winter>();
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

void SeasonFactory::initialize_season_map()
{
  season_map.clear();

  ISeasonPtr spring = std::make_shared<Spring>();
  ISeasonPtr summer = std::make_shared<Summer>();
  ISeasonPtr autumn = std::make_shared<Autumn>();
  ISeasonPtr winter = std::make_shared<Winter>();

  season_map.insert(make_pair(CLASS_ID_SPRING, spring));
  season_map.insert(make_pair(CLASS_ID_SUMMER, summer));
  season_map.insert(make_pair(CLASS_ID_AUTUMN, autumn));
  season_map.insert(make_pair(CLASS_ID_WINTER, winter));
}