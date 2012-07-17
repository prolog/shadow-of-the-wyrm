#pragma once
#include "Creature.hpp"
#include "Map.hpp"

class Detection
{
  public:
    void detect_creatures_if_necessary(CreaturePtr player, MapPtr map, const std::string& original_map_id, const std::string& current_map_id);
};
