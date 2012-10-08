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

