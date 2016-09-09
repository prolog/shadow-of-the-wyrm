#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/regex.hpp>
#include "zlib.h" // compression
#include "global_prototypes.hpp"
#include "CompilationDetails.hpp"
#include "Conversion.hpp"
#include "Environment.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Metadata.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "Serialization.hpp"
#include "Serialize.hpp"

using namespace std;
using namespace boost::algorithm;
using namespace boost::filesystem;

// Save the entire game state to disk
void Serialization::save(CreaturePtr creature)
{
  Game& game = Game::instance();

  try
  {
    // Get the creature's name
    string name;

    if (creature)
    {
      name = creature->get_name();
    }
    
    CreaturePtr player = game.get_current_player();

    Metadata meta(player);

    // Get the user's name
    string user_name = meta.get_user_name();
    string filename = generate_savefile_name(user_name, name);

    // Name the file and do the appropriate setup
    std::ofstream stream(filename, ios::binary | ios::out);

    // Create a stream for the game data (can be compressed or uncompressed).
    ostringstream game_stream;
        
    // Save the state and game data:

    // Save the metadata
    meta.serialize(stream);

    Settings& settings = game.get_settings_ref();
    bool use_compression = String::to_bool(settings.get_setting("savefile_compression"));
    int compression_level = String::to_int(settings.get_setting("compression_level"));
    Serialize::write_bool(stream, use_compression);
    Serialize::write_int(stream, compression_level);

    // Write the remaining settings: RNG, message buffer.
    // These are not massive, so they can be left uncompressed.
    Serialize::write_uint(stream, RNG::get_seed());
    MessageBuffer mb = MessageManagerFactory::instance().get_message_buffer();
    mb.serialize(stream);

    // Save the game details.  This is where the bulk of the size comes from -
    // this can be compressed after to save a lot of disk space.
    game.serialize(game_stream);

    // Write the game data, either compressed or uncompressed, depending on the
    // settings in the ini file.
    write_savefile(stream, game_stream, use_compression, compression_level);
  }
  catch(...)
  {
    // JCD FIXME: Custom exception here
  }
}

void Serialization::write_savefile(std::ofstream& file_stream, ostringstream& game_stream, const bool use_compression, const int compression_level)
{
  string game_data = game_stream.str();

  try
  {
    if (use_compression)
    {
      unsigned long data_size = game_data.size();
      unsigned long compressed_size = data_size;
      vector<Bytef> compressed_game_data(compressed_size);
      int ret_code = compress2(&compressed_game_data[0], &compressed_size, reinterpret_cast<const Bytef*>(game_data.c_str()), data_size, compression_level);
      
      if (ret_code == Z_OK)
      {
        // First, write the uncompressed and compressed size.
        Serialize::write_ulong(file_stream, data_size);
        Serialize::write_ulong(file_stream, compressed_size);

        // Then, write the compressed data to file.  write() needs to be used
        // instead of operator<< because the latter expects a null-terminated
        // string.
        file_stream.write(reinterpret_cast<const char *>(&compressed_game_data[0]), compressed_size);
        return;
      }
    }

    file_stream << game_data;
  }
  catch (...)
  {
    Log::instance().error("Error writing to savefile!");
  }
}

// Restore the game state from a particular file
SerializationReturnCode Serialization::load(const string& filename)
{
  std::ifstream fstream;

  // Once the savefile is decompressed, read in the save details.
  fstream.open(filename, ios::in | ios::binary);

  read_savefile(fstream);

  return SerializationReturnCode::SERIALIZATION_OK;
}

// Read the savefile from the string, decompressing as needed.
void Serialization::read_savefile(std::ifstream& stream)
{
  bool use_compression = false;
  int compression_level = Z_DEFAULT_COMPRESSION;

  Metadata meta;
  meta.deserialize(stream);

  // Get the serialized value to determine if savefile compression is used
  // for the game data.
  Serialize::read_bool(stream, use_compression);
  Serialize::read_int(stream, compression_level);

  uint rng_seed = 0;
  Serialize::read_uint(stream, rng_seed);

  RNG::set_seed(rng_seed);
  RNG::initialize();

  MessageBuffer mb;
  mb.deserialize(stream);
  MessageManagerFactory::instance().set_message_buffer(mb);

  try
  {
    if (use_compression)
    {
      unsigned long uncomp_size, comp_size;
      Serialize::read_ulong(stream, uncomp_size);
      Serialize::read_ulong(stream, comp_size);

      ostringstream game_stream;
      vector<Bytef> game_data_comp(comp_size);
      vector<Bytef> uncompressed(uncomp_size);

      // Read the compressed data.
      stream.read(reinterpret_cast<char*>(&game_data_comp[0]), comp_size);

      // Uncompress the compressed data.
      uncompress(&uncompressed[0], &uncomp_size, &game_data_comp[0], comp_size);

      // Now we've got an uncompressed byte stream.
      // Copy it to an istream& so it can be read by deserialize.
      std::istringstream uncomp_game_stream(std::string(reinterpret_cast<char*>(&uncompressed[0]), uncompressed.size()));
      read_game_stream(uncomp_game_stream);
    }
    else
    {
      read_game_stream(stream);
    }
  }
  catch (std::exception& error)
  {
    string error_msg = error.what();
    Log::instance().error("Error while reading savefile: " + error_msg);
  }
}

// Read the game data from an istream.
// The assumption is that this is either the original file stream (if the
// data was never compressed), or an istringstream (if the data was
// decompressed from the compressed data stored in the original file
// stream).
void Serialization::read_game_stream(istream& stream)
{
  Game& game = Game::instance();
  game.deserialize(stream);
}

bool Serialization::delete_savefile(const string& filename)
{
  path savefile(filename);
  return remove(savefile);
}

// Generate the savefile name based on the user name and character name provided.
string Serialization::generate_savefile_name(const string& user_name, const string& character_name)
{
  string string_to_hash = trim_copy(user_name) + "_" + trim_copy(character_name);

  // Convert the string to lower case so that we don't care about whether the user is named
  // "FOO" or "foo" or "foo    ", etc.
  to_lower(string_to_hash); 
  
  boost::hash<string> string_hash;
  size_t hash = string_hash(string_to_hash);
  string savefile_name = "./" + std::to_string(hash) + ".sws"; // "sws" = "Shadow of the Wyrm Save"

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

  boost::regex e(FileConstants::SAVEFILE_PATTERN);

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

  std::ifstream save_file;

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

      string compilation_details_from_file;
      Serialize::read_string(save_file, compilation_details_from_file);

      CompilationDetails cd;
      string current_compilation_details = cd.get_compilation_details_string();

      string character_synopsis_from_file;
      Serialize::read_string(save_file, character_synopsis_from_file);

      bool save_file_available = true;

      save_file_available = save_file_available && ((user_name_from_file == current_user) || user_name_from_file.empty());
      save_file_available = save_file_available && (version_from_file == current_version);
      save_file_available = save_file_available && (compilation_details_from_file == current_compilation_details);

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
