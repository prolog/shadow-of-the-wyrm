#include <boost/make_shared.hpp>
#include "WorldFactory.hpp"

WorldFactory::WorldFactory()
{
}

WorldFactory::~WorldFactory()
{
}

WorldPtr WorldFactory::create_world()
{
  WorldPtr world = boost::make_shared<World>();

  return world;
}

