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
    static SerializationReturnCode load();
    static std::vector<std::pair<std::string, std::string>> get_save_file_names();
};

