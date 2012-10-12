#include <boost/make_shared.hpp>
#include "MapFactory.hpp"

MapFactory::MapFactory()
{
}

MapFactory::~MapFactory()
{
}

MapPtr MapFactory::create_map()
{
  Dimensions d;
  MapPtr map = boost::make_shared<Map>(d);

  return map;
}

MapExitPtr MapFactory::create_map_exit()
{
  MapExitPtr map_exit = boost::make_shared<MapExit>();

  return map_exit;
}
