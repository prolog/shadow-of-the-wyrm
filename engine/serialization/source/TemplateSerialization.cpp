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
  // JCD FIXME: Are these needed, or can they be built up on load?
  ar << game->deities << game->races << game->classes;
  ar << game->map_registry;
}

SerializationReturnCode TemplatesSerialization::load()
{
  return SERIALIZATION_OK;
}

// these do the actual serialization.
// fuck you, MinGW
namespace boost
{
  namespace serialization
  {
    template<typename Archive>
    void serialize(Archive& ar, Deity& d, const unsigned int version)
    {
      ar & d.id & d.name_sid & d.description_sid & d.short_description_sid;
      ar & d.death_message_sid & d.alignment_range & d.worship_site_type & d.initial_statistics_modifier;
    }
  }
}
