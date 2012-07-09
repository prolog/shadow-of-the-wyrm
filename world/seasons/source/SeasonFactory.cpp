#include <boost/make_shared.hpp>
#include "SeasonFactory.hpp"
#include "Spring.hpp"
#include "Summer.hpp"
#include "Autumn.hpp"
#include "Winter.hpp"

using boost::make_shared;

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
      new_season = make_shared<Spring>();
      break;
    case SEASON_SUMMER:
      new_season = make_shared<Summer>();
      break;
    case SEASON_AUTUMN:
      new_season = make_shared<Autumn>();
      break;
    case SEASON_WINTER:
    default:
      new_season = make_shared<Winter>();
      break;
  }

  return new_season;
}
