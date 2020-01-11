#include "MapRegistry.hpp"
#include "Log.hpp"
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
  bool inserted = (map_registry.insert(make_pair(map_id, map))).second;
  return inserted;
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

void MapRegistry::clear_maps()
{
  map_registry.clear();
}

MapRegistryMap& MapRegistry::get_maps_ref()
{
  return map_registry;
}

void MapRegistry::add_symbol_to_cache(const string& key, const Symbol& s)
{
  symbol_cache[key] = s;
}

pair<bool, Symbol> MapRegistry::cache_has_symbol(const string& key) const
{
  pair<bool, Symbol> cache_details = {false, Symbol('?', Colour::COLOUR_WHITE)};

  auto c_it = symbol_cache.find(key);
  if (c_it != symbol_cache.end())
  {
    cache_details = {true, c_it->second};
  }

  return cache_details;
}

void MapRegistry::clear_symbol_cache()
{
  symbol_cache.clear();
}

bool MapRegistry::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, map_registry.size());

  for (const MapRegistryMap::value_type& map_pair : map_registry)
  {
    string map_guid = map_pair.first;
    MapPtr map = map_pair.second;

    Serialize::write_string(stream, map_guid);

    Serialize::write_class_id(stream, map->get_class_identifier());
    map->serialize(stream);
  }

  Serialize::write_size_t(stream, symbol_cache.size());

  for (auto& scache_pair : symbol_cache)
  {
    Serialize::write_string(stream, scache_pair.first);
    scache_pair.second.serialize(stream);
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

  size_t num_cached_symbols = 0;
  Serialize::read_size_t(stream, num_cached_symbols);

  for (size_t i = 0; i < num_cached_symbols; i++)
  {
    string key;
    Serialize::read_string(stream, key);

    Symbol s('?', Colour::COLOUR_WHITE);
    s.deserialize(stream);

    symbol_cache[key] = s;
  }

  return true;
}

ClassIdentifier MapRegistry::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP_REGISTRY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapRegistry_test.cpp"
#endif

