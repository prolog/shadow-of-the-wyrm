#pragma once
#include "Race.hpp"

class RaceManager
{
  public:
    RaceManager();

    RacePtr get_race(const std::string& race_id);
};
