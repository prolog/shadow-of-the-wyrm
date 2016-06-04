#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "SelectTileTypes.hpp"
#include "Map.hpp"

class SelectionUtils
{
  public:
    // select the nearest hostile creature.  This is done so that the player doesn't have to constantly select
    // a creature to target when 'f'ire is selected.
    static std::string select_nearest_hostile_target(CreaturePtr creature, MapPtr current_map);

    // Select the existing ranged combat target for the given creature, on the given map.
    // Return true if the existing target was selected, false if the cursor was reset.
    static bool select_existing_target(CreaturePtr creature, MapPtr map);

    // Select the previous or next target from the current target.
    // Return the creature ID of the targetted creature
    static std::string select_target_in_cycle(CreaturePtr creature, MapPtr map, const SelectCreatureType sct);

    // Check to see if the creature has a target for the given attack type.
    static bool has_target(CreaturePtr creature, const AttackType attack_type);

    // Set the target for a given creature and attack type.
    static void set_target(CreaturePtr creature, const AttackType attack_type, const std::pair<std::string, Coordinate>& target_pair, MapPtr map);

  private:
    SelectionUtils();
    ~SelectionUtils();
};