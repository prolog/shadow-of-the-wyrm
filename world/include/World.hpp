#pragma once
#include <boost/shared_ptr.hpp>
#include "Map.hpp"

class World
{
  public:
    World();
    ~World();

  protected:
    MapPtr world_map;
};

typedef boost::shared_ptr<World> WorldPtr;
