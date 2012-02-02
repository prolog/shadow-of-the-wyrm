#include "MapRegistry.hpp"

using std::map;
using std::string;

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
