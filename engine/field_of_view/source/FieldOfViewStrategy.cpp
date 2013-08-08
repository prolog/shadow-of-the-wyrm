#include "CurrentCreatureAbilities.hpp"
#include "FieldOfViewStrategy.hpp"

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
      tile->set_viewed(true);      
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

