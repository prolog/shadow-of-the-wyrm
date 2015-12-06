#pragma once
#include <string>
#include <map>
#include <vector>
#include "common.hpp"
#include "CreatureFeatures.hpp"

using SyllableMap = std::map<CreatureSex, std::map<int, std::map<int, std::vector<std::string>>>>;

class Naming
{
  public:
    static std::string generate_name(const CreatureSex sex);
    static std::string clean_name(const std::string& name);
    static std::string clean_name_or_use_default(const std::string& name, const CreatureSex sex);
    static uint get_max_name_size();

  protected:
    Naming();

    static std::string create_name(const int num_syllables, const std::map<int, std::map<int, std::vector<std::string>>>& syl_map_entry);
    static uint MAXIMUM_NAME_SIZE;
    static const int MIN_NAME_SYL;
    static const int MAX_NAME_SYL;

    // Map from number of syllables to potential syllables for each place.
    static const SyllableMap syllables;
};
