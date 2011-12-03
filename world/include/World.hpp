#pragma once
#include <boost/shared_ptr.hpp>
#include "Map.hpp"

class World
{
  public:
    World(MapPtr new_world_map);
    ~World();

    void set_world(MapPtr new_world_map);
    MapPtr get_world() const;

  protected:
    MapPtr world_map;
};

typedef boost::shared_ptr<World> WorldPtr;
