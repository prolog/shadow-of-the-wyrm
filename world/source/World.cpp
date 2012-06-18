#include "World.hpp"

World::World(MapPtr new_world_map) : world_map(new_world_map)
{
}

World::~World()
{
}

void World::set_world(MapPtr new_world_map)
{
  world_map = new_world_map;
}

MapPtr World::get_world() const
{
  return world_map;
}

Calendar& World::get_calendar()
{
  return calendar;
}
