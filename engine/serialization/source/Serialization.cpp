#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/functional/hash.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "Environment.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Serialization.hpp"
#include "TemplatesSerialization.hpp"

using namespace std;
using namespace boost::archive;

// Save the entire game state to disk
void Serialization::save(CreaturePtr creature)
{
  try
  {
    // Get the creature's name
    string name;

    if (creature)
    {
      name = creature->get_name();
    }
    
    // Get the user's name
    string user_name = Environment::get_user_name();
    string string_to_hash = user_name + name;
    boost::hash<string> string_hash;
    size_t hash = string_hash(string_to_hash);
    string filename = Integer::to_string(hash) + ".sls"; // "sls" = "Savage Lands Save"

    // Name the file and do the appropriate setup
    ofstream ofs(filename.c_str());
    text_oarchive ar(ofs);
    
    // Save the metadata
    string version = get_version();
    
    ar << user_name;
    ar << version;
    
    // Save the game data
    // Game
    Game* game = Game::instance();
    TemplatesSerialization::save(ar, game);
//    ar << game;
    // RNG
  }
  catch(boost::archive::archive_exception ae)
  {
    string ae_error = ae.what();
    Log::instance()->log(ae_error);
  }
}

// Restore the game state from a particular file
SerializationReturnCode Serialization::load()
{
  // JCD FIXME
  
  return SERIALIZATION_OK;
}
