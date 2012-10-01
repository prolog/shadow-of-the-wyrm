#include "MapRegistry.hpp"
#include "World.hpp"

World::World(MapPtr new_world_map) : world_map_id(new_world_map->get_map_id())
{
}

World::~World()
{
}

void World::set_world(MapPtr new_world_map)
{
  world_map_id = new_world_map->get_map_id();
}

MapPtr World::get_world(const MapRegistry& registry) const
{
  MapPtr world_map;
  
  world_map = registry.get_map(world_map_id);
  
  return world_map;
}

Calendar& World::get_calendar()
{
  return calendar;
}
