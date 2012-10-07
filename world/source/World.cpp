#include "MapRegistry.hpp"
#include "Serialize.hpp"
#include "World.hpp"

World::World()
{
}

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

bool World::serialize(std::ostream& stream)
{
  Serialize::write_string(stream, world_map_id);
  calendar.serialize(stream);

  return true;
}

bool World::deserialize(std::istream& stream)
{
  Serialize::read_string(stream, world_map_id);
  calendar.deserialize(stream);

  return true;
}

ClassIdentifier World::internal_class_identifier() const
{
  return CLASS_ID_WORLD;
}