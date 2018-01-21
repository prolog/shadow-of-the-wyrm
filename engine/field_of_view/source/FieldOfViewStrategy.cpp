#include "CurrentCreatureAbilities.hpp"
#include "CreatureFeatures.hpp"
#include "FieldOfViewStrategy.hpp"
#include "Game.hpp"

FieldOfViewStrategy::FieldOfViewStrategy(const bool set_fov_flag)
: set_fov_tile_view_flag(set_fov_flag)
{  
}

void FieldOfViewStrategy::add_point_to_map(CreaturePtr fov_creature, const Coordinate& c, MapPtr view_map, MapPtr fov_map)
{
  TilePtr tile = view_map->at(c);

  CurrentCreatureAbilities cca;
  bool creature_blinded = !cca.can_see(fov_creature);
  
  if (tile)
  {
    if (set_fov_tile_view_flag && !creature_blinded)
    {
      // Only set a tile viewed when doing the player's FOV calculations.
      if (fov_creature != nullptr &&
          fov_creature->get_id() == CreatureID::CREATURE_ID_PLAYER &&
          tile->get_viewed() == false)
      {
        set_tile_viewed(c);
      }
    }

    if (!creature_blinded || 
         (creature_blinded && 
          fov_creature && 
          tile && 
          tile->get_creature() && 
          tile->get_creature()->get_id() == fov_creature->get_id()))
    {
      fov_map->insert(c.first, c.second, tile);
    }
  }
}

// View maps work with copies of tiles so that non-destructive changes can be
// made when creatures are hidden, etc.  Because these are copies of the
// "real" tiles, we need to grab to real tile off the current map to 
// authoritatively set the viewed flag.
void FieldOfViewStrategy::set_tile_viewed(const Coordinate& c)
{
  MapPtr master_map = Game::instance().get_current_map();

  if (master_map != nullptr)
  {
    TilePtr master_tile = master_map->at(c);

    if (master_tile != nullptr)
    {
      master_tile->set_viewed(true);
    }
  }
}