#include "MapRegistry.hpp"
#include "Serialize.hpp"
#include "World.hpp"

using namespace std;

World::World()
{
}

World::World(MapPtr new_world_map) : world_map_id(new_world_map->get_map_id())
{
}

World::~World()
{
}

bool World::operator==(const World& world)
{
  bool result = true;

  result = result && (world_map_id == world.world_map_id);
  result = result && (calendar == world.calendar);

  return result;
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

#ifdef UNIT_TESTS
#include "unit_tests/World_test.cpp"
#endif
