#pragma once
#include <boost/shared_ptr.hpp>
#include "Calendar.hpp"
#include "Map.hpp"

class World
{
  public:
    World(MapPtr new_world_map);
    ~World();

    void set_world(MapPtr new_world_map);
    MapPtr get_world() const;
    
    Calendar& get_calendar();

  protected:
    MapPtr world_map;
    Calendar calendar;
};

typedef boost::shared_ptr<World> WorldPtr;
