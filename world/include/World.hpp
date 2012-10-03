#pragma once
#include <boost/shared_ptr.hpp>
#include "Calendar.hpp"
#include "Map.hpp"

class MapRegistry;

class World
{
  public:
    World(MapPtr new_world_map);
    ~World();

    void set_world(MapPtr new_world_map);
    MapPtr get_world(const MapRegistry& map_registry) const;
    
    Calendar& get_calendar();

  protected:
    std::string world_map_id;
    Calendar calendar;
};

typedef boost::shared_ptr<World> WorldPtr;
