#include "WorldFactory.hpp"

WorldFactory::WorldFactory()
{
}

WorldFactory::~WorldFactory()
{
}

WorldPtr WorldFactory::create_world()
{
  WorldPtr world = std::make_shared<World>();

  return world;
}

