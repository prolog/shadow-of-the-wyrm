#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class RangedCombatAction : public IActionManager
{
  public:
    bool operator==(const RangedCombatAction& rca) const;
    ActionCostValue fire_missile(CreaturePtr creature);

  protected:
    friend class ActionManager;
    RangedCombatAction();
    
    // Get the selected tile.  Once this function has finished,
    // the target map on the creature will have the appropriate tile.
    ActionCostValue get_selected_tile(CreaturePtr creature);
    
    // Get the actual coordinates to fire at.  This takes into account
    // the flight of the missile along a particular line, and whether there
    // are any creatures or blocking tiles along the way.
    std::vector<Coordinate> get_actual_coordinates_given_missile_path(const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr map);
    
    // Fire at the given coordinates: attack the creature on the tile,
    // if present, and then either destroy or drop the ammunition.
    void fire_at_given_coordinates(CreaturePtr creature, MapPtr map, const Coordinate& coordinate);
    
    // Add a ranged combat message based on whether a launcher is being used, whether a creature is being targetted,
    // and whether the attacking creature is the player or ont.
    void add_ranged_combat_message(CreaturePtr attacking_creature, CreaturePtr target_creature);
    
    // Either destroy the ammo (it didn't survive being fired), or drop it
    // on the appropriate tile.
    void destroy_ammunition_or_drop_on_tile(CreaturePtr creature, TilePtr tile);
    
    // Fire creature's weapon at the tile, checking to see if
    // anything is hit along the way.
    void fire_weapon_at_tile(CreaturePtr creature);
    
    // Check to see if the creature has a ranged combat target selected.
    bool has_ranged_combat_target(CreaturePtr creature);
    
    // select the nearest hostile creature.  This is done so that the player doesn't have to constantly select
    // a creature to target when 'f'ire is selected.
    void select_nearest_hostile_target(CreaturePtr creature, MapPtr current_map);
    
    // Select the existing ranged combat target for the given creature, on the given map.
    void select_existing_target(CreaturePtr creature, MapPtr map);
    
    ActionCostValue get_action_cost_value() const;
};
