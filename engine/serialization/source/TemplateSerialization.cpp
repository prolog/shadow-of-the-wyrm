#include <boost/serialization/base_object.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>
#include "Game.hpp"
#include "TemplatesSerialization.hpp"

#include "ClassSerializationExports.hpp"

// Serializes all the Game class templates maps (races, classes, deities, etc).
// This is all done separately instead of in a function in Game becaues MinGW
// dies otherwise.
void TemplatesSerialization::save(boost::archive::text_oarchive& ar, Game* game)
{
  // Races, classes, and deities are reloaded each game from disk.
  // 
  // The map registry, which contains maps (which contains tiles which contains creatures, items, and features)
  // is what actually gets persisted.
  ar << game->map_registry;
}

SerializationReturnCode TemplatesSerialization::load()
{
  return SERIALIZATION_OK;
}
