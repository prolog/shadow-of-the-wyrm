#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/regex.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "Environment.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Metadata.hpp"
#include "RNG.hpp"
#include "Serialization.hpp"
#include "Serialize.hpp"

using namespace std;
using namespace boost::filesystem;

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
    
    Metadata meta;

    // Get the user's name
    string user_name = meta.get_user_name();
    string filename = generate_savefile_name(user_name, name);

    // Name the file and do the appropriate setup
    ofstream stream(filename, ios::binary);
        
    // Save the state and game data
    if (game)
    {
      // Save the metadata
      meta.serialize(stream);

      // Save the game and RNG data
      game->serialize(stream);
      Serialize::write_uint(stream, RNG::get_seed());
    }
  }
  catch(...)
  {
    // JCD FIXME: Custom exception here
  }
}

// Restore the game state from a particular file
SerializationReturnCode Serialization::load(const string& filename)
{
  Game* game = Game::instance();
  ifstream stream;

  if (game)
  {
    stream.open(filename, ios::in | ios::binary);

    Metadata meta;
    uint rng_seed = 0;

    meta.deserialize(stream);
    game->deserialize(stream);
    Serialize::read_uint(stream, rng_seed);

    RNG::set_seed(rng_seed);
    RNG::reinitialize();
  }
  else
  {
    return SERIALIZATION_ERROR;
  }

  if (stream.is_open())
  {
    stream.close();
  }

  return SERIALIZATION_OK;
}

bool Serialization::delete_savefile(const string& filename)
{
  path savefile(filename);
  return remove(savefile);
}

// Generate the savefile name based on the user name and character name provided.
string Serialization::generate_savefile_name(const string& user_name, const string& character_name)
{
  string string_to_hash = user_name + "_" + character_name;
  boost::hash<string> string_hash;
  size_t hash = string_hash(string_to_hash);
  string savefile_name = "./" + Integer::to_string(hash) + ".sls"; // "sls" = "Savage Lands Save"

  return savefile_name;
}

bool Serialization::does_savefile_exist_for_user_and_character(const string& user_name, const string& character_name)
{
  string filename = generate_savefile_name(user_name, character_name);
  path save_file_filter(filename);

  return (exists(save_file_filter));
}

// JCD FIXME SPLIT THESE INTO THEIR OWN CLASS.

// Get a list of savefile names for the current user.
vector<pair<string, string>> Serialization::get_save_file_names()
{
  vector<pair<string,string>> save_files;
  string user_name = Environment::get_user_name();
  path save_file_filter(".");
  directory_iterator end_it;

  boost::regex e(".(sls)$");

  if (exists(save_file_filter))
  {
    for (directory_iterator d_it(save_file_filter); d_it != end_it; d_it++)
    {
      string filename = d_it->path().string();

      if (boost::regex_search(filename,e))
      {
        pair<bool, string> save_file_availability = get_save_file_availability_and_synopsis(d_it->path().string());

        if (save_file_availability.first == true)
        {
          save_files.push_back(make_pair(filename, save_file_availability.second));
        }
      }
    }
  }

  return save_files;
}

// Check to see if the save file is available.  This is done by:
// - Checking the user name stored in the file.  This must match the
//   current user's name.
// - Checking the version stored in the file.  The version must
//   match exactly.
// - Checking the compiler info stored in the file.  This must
//   exactly match.
pair<bool, string> Serialization::get_save_file_availability_and_synopsis(const string& filename)
{
  pair<bool, string> save_file_availability(false, "");

  ifstream save_file;

  try
  {
    save_file.open(filename, ios::in | ios::binary);

    if (save_file.good())
    {
      Metadata meta;

      string user_name_from_file;
      Serialize::read_string(save_file, user_name_from_file);
      string current_user = Environment::get_user_name();

      string version_from_file;
      Serialize::read_string(save_file, version_from_file);
      string current_version = meta.get_version();

      string compiler_details_from_file;
      Serialize::read_string(save_file, compiler_details_from_file);
      string current_compiler = meta.get_compiler_details();

      string character_synopsis_from_file;
      Serialize::read_string(save_file, character_synopsis_from_file);

      bool save_file_available = true;

      save_file_available &= (user_name_from_file == current_user);
      save_file_available &= (version_from_file == current_version);
      save_file_available &= (compiler_details_from_file == current_compiler);

      save_file_availability.first = save_file_available;

      if (save_file_available)
      {
        save_file_availability.second = character_synopsis_from_file;
      }
    }
  }
  catch(...)
  {
  }

  save_file.close();

  return save_file_availability;
}