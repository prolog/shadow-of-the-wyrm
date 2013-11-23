#include "MapRegistry.hpp"
#include "Serialize.hpp"

// Needed for serialization
#include "MapFactory.hpp"

using namespace std;

MapRegistry::MapRegistry()
{
}

MapRegistry::~MapRegistry()
{
  map_registry.clear();
}

// Add a map to the registry.  Return false if a map with the given
// ID already exists.
bool MapRegistry::set_map(const string& map_id, const MapPtr& map)
{
  return (map_registry.insert(make_pair(map_id, map))).second;
}

// Get a map from the registry.  Return a null shared ptr if the map
// with the given ID doesn't exist.
MapPtr MapRegistry::get_map(const string& map_id) const
{
  MapPtr map;
  std::map<string, MapPtr>::const_iterator r_it = map_registry.find(map_id);

  if (r_it != map_registry.end())
  {
    map = r_it->second;
  }

  return map;
}

// Remove a map with the given ID from the registry.  Return false
// if the map doesn't exist.
bool MapRegistry::remove_map(const string& map_id)
{
  bool map_removed = false;
  map<string, MapPtr>::iterator r_it = map_registry.find(map_id);
  
  if (r_it != map_registry.end())
  {
    map_registry.erase(r_it);
    map_removed = true;
  }
  
  return map_removed;
}

bool MapRegistry::serialize(ostream& stream)
{
  Serialize::write_size_t(stream, map_registry.size());

  for (MapRegistryMap::value_type& map_pair : map_registry)
  {
    string map_guid = map_pair.first;
    MapPtr map = map_pair.second;

    Serialize::write_string(stream, map_guid);

    Serialize::write_class_id(stream, map->get_class_identifier());
    map->serialize(stream);
  }

  return true;
}

bool MapRegistry::deserialize(istream& stream)
{
  size_t map_registry_size;
  Serialize::read_size_t(stream, map_registry_size);

  map_registry.clear();

  for (unsigned int i = 0; i < map_registry_size; i++)
  {
    string map_guid;
    Serialize::read_string(stream, map_guid);

    // There's only one kind of map - consume and ignore the class ID for now.
    ClassIdentifier map_clid;
    Serialize::read_class_id(stream, map_clid);
    MapPtr map = MapFactory::create_map();
    map->deserialize(stream);

    map_registry.insert(make_pair(map_guid, map));
  }

  return true;
}

ClassIdentifier MapRegistry::internal_class_identifier() const
{
  return CLASS_ID_MAP_REGISTRY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapRegistry_test.cpp"
#endif

