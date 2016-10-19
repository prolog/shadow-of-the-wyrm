#pragma once
#include "Race.hpp"

class RaceManager
{
  public:
    RaceManager();

    RacePtr get_race(const std::string& race_id);

    // Returns true if race_id = race_to_match, or if the race identified
    // by race_id is a descendent in the race hierarchy of the race represented
    // by race_to_match.
    bool is_race_or_descendent(const std::string& race_id, const std::string& race_to_match);

    // Aggregates all the drop chances from the current race up to the parent.
    std::map<std::string, DropParameters> get_all_drops(const std::string& race_id);
};
