#pragma once
#include "Creature.hpp"

class RangedCombatUtils
{
  public:
    static bool is_coord_in_range(const Coordinate& c, MapPtr view_map);

    // Check to see that there's nothing in the missile flight path that would
    // block the way
    static bool is_coordinate_obstacle_free(CreaturePtr firing_creature, const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr current_map);

    // Get the actual coordinates to fire at.  This takes into account
    // the flight of the missile along a particular line, and whether there
    // are any creatures or blocking tiles along the way.
    static std::vector<Coordinate> get_actual_coordinates_given_missile_path(CreaturePtr firing_creature, const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr map);
};