#pragma once
#include <string>
#include <vector>
#include "Creature.hpp"
#include "Environment.hpp"
#include "SerializationTypes.hpp"

class Serialization
{
  public:
    static std::string save(CreaturePtr creature);
    static SerializationReturnCode load(const std::string& filename);
    static bool delete_savefile(const std::string& filename);

    static std::string generate_savefile_name(const std::string& user_name, const std::string& character_name);
    static bool does_savefile_exist_for_user_and_character(const std::string& user_name, const std::string& character_name);

    static std::vector<std::pair<std::string, std::string>> get_save_file_names(const bool single_user_mode, const bool skip_metadata_verification);

  protected:
    static std::pair<bool, std::string> get_save_file_availability_and_synopsis(const std::string& file, const bool single_user_mode, const bool skip_metadata_verification);
    static void write_savefile(std::ofstream& file_stream, std::ostringstream& gamedata_stream, const bool use_compression, const int compression_level);
    static void read_savefile(std::ifstream& stream);
    static void read_game_stream(std::istream& stream);
};

