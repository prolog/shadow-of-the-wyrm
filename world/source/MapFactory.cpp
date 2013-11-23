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
  MapPtr map = std::make_shared<Map>(d);

  return map;
}

MapExitPtr MapFactory::create_map_exit()
{
  MapExitPtr map_exit = std::make_shared<MapExit>();

  return map_exit;
}
