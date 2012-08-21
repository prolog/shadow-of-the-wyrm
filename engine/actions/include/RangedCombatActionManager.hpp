#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class RangedCombatActionManager : public IActionManager
{
  public:
    ActionCostValue fire_missile(CreaturePtr creature);

  protected:
    friend class ActionManager;
    RangedCombatActionManager();
    
    // Get the selected tile.  Once this function has finished,
    // the target map on the creature will have the appropriate tile.
    ActionCostValue get_selected_tile(CreaturePtr creature);
    
    // Get the actual coordinates to fire at.  This takes into account
    // the flight of the missile along a particular line, and whether there
    // are any creatures or blocking tiles along the way.
    Coordinate get_actual_coordinates_given_missile_path(const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr map);
    
    // Fire at the given coordinates: attack the creature on the tile,
    // if present, and then either destroy or drop the ammunition.
    void fire_at_given_coordinates(CreaturePtr creature, MapPtr map, const Coordinate& coordinate);
    
    // Either destroy the ammo (it didn't survive being fired), or drop it
    // on the appropriate tile.
    void destroy_ammunition_or_drop_on_tile(CreaturePtr creature, TilePtr tile);
    
    // Fire creature's weapon at the tile, checking to see if
    // anything is hit along the way.
    void fire_weapon_at_tile(CreaturePtr creature);
    
    ActionCostValue get_action_cost_value() const;
};
