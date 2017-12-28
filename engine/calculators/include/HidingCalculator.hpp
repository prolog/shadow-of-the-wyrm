#pragma once
#include "Creature.hpp"
#include "Map.hpp"
#include "Date.hpp"

class HidingCalculator
{
  public:
    int calculate_pct_chance_hide(CreaturePtr creature, MapPtr map, const TimeOfDayType tod) const;

  protected:
    int get_tod_hide_modifier_for_map_type(const TimeOfDayType tod, const MapType map_type) const;
    int get_viewing_creatures_modifier(CreaturePtr creature, MapPtr map, const std::vector<std::string>& viewing_creature_ids) const;
    int get_distance_modifier(const int dist) const;

    static const int MAX_DISTANCE_FOR_PENALTY;
};

