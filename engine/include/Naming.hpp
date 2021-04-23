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

    static std::string generate_settlement_name();

  protected:
    Naming();

    // Names are defined for Male and Female.  If sex isn't specified, pick one
    // of the sexes at random and use that for generating a random name.
    static SyllableMap::const_iterator find_in_syllables(const CreatureSex cs);

    static std::string create_name(const int num_syllables, const std::map<int, std::map<int, std::vector<std::string>>>& syl_map_entry);

    static std::string generate_locative_settlement_name();
    static std::string generate_possessive_settlement_name();
    static std::string generate_descriptive_settlement_name();
    static std::string generate_random_settlement_name();
    static std::string generate_base_random_settlement_name();

    static uint MAXIMUM_NAME_SIZE;
    static const int MIN_NAME_SYL;
    static const int MAX_NAME_SYL;

    // Map from number of syllables to potential syllables for each place.
    static const SyllableMap syllables;
    static const std::map<int, std::vector<std::string>> settlement_syllables;
};
