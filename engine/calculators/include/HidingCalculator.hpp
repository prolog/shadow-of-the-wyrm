#pragma once
#include "Creature.hpp"
#include "Map.hpp"
#include "Date.hpp"

class HidingCalculator
{
  public:
    std::pair<int, std::vector<std::string>> calculate_pct_chance_hide(CreaturePtr creature, MapPtr map, const TimeOfDayType tod) const;
    int calculate_pct_chance_hidden_after_attacking(CreaturePtr creature);
    bool gets_hole_bonus(CreaturePtr creature) const;

  protected:
    int get_tod_hide_modifier_for_map_type(const TimeOfDayType tod, const MapType map_type) const;
    std::pair<int, std::vector<string>> get_viewing_creatures_modifier(CreaturePtr creature, MapPtr map, const std::vector<std::string>& viewing_creature_ids) const;
    int get_distance_modifier(const int dist) const;

    static const int HIDING_DIVISOR_AFTER_ATTACKING;
    static const int MAX_DISTANCE_FOR_PENALTY;
    static const int MAX_PCT_CHANCE_HIDE_CREATURES_PRESENT;
    static const int SMALL_CREATURE_HOLE_BONUS;
};

