#include <fstream>
#include <boost/functional/hash/hash.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "Environment.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "RNG.hpp"
#include "Serialization.hpp"
#include "Serialize.hpp"

using namespace std;

// Save the entire game state to disk
void Serialization::save(CreaturePtr creature)
{
  Game* game = Game::instance();

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
    std::ofstream save_file(filename, ios::binary);
    
    // Save the metadata
    string version = get_version();
    
    // Save the state and game data
    if (game)
    {
      Serialize::write_uint(save_file, RNG::get_seed());
      game->serialize(save_file);
    }
  }
  catch(...)
  {
    // JCD FIXME: Custom exception here
  }
}

// Restore the game state from a particular file
SerializationReturnCode Serialization::load()
{
  // JCD FIXME  
  return SERIALIZATION_OK;
}
