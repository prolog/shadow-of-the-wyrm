#pragma once
#include <string>
#include <vector>
#include "Creature.hpp"
#include "Environment.hpp"
#include "SerializationTypes.hpp"

class Serialization
{
  public:
    static void save(CreaturePtr creature);
    static SerializationReturnCode load(const std::string& filename);
    static std::vector<std::pair<std::string, std::string>> get_save_file_names();

  protected:
    static std::pair<bool, std::string> get_save_file_availability_and_synopsis(const std::string& file);
};

