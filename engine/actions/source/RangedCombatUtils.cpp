#include "RangedCombatUtils.hpp"
#include "BresenhamLine.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "RNG.hpp"

using namespace std;

bool RangedCombatUtils::is_coordinate_obstacle_free(CreaturePtr firing_creature, const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr current_map)
{
  bool obstacle_free = false;
  vector<Coordinate> actual = get_actual_coordinates_given_missile_path(firing_creature, creature_coords, target_coords, current_map);

  if (!actual.empty())
  {
    Coordinate last = actual.back();
    obstacle_free = (target_coords == last);
  }

  return obstacle_free;
}

// Get the actual coordinates to fire at, given the missile's flight path.
vector<Coordinate> RangedCombatUtils::get_actual_coordinates_given_missile_path(CreaturePtr firing_creature, const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr current_map)
{
  vector<Coordinate> actual_coordinates;
  int pct_chance_fire_through = 0;
  CombatTargetNumberCalculatorPtr ctnc = CombatTargetNumberCalculatorFactory::create_target_number_calculator(AttackType::ATTACK_TYPE_RANGED);

  BresenhamLine bl;
  vector<Coordinate> line_points = bl.get_points_in_line(creature_coords.first, creature_coords.second, target_coords.first, target_coords.second);

  TilePtr tile;
  for (const Coordinate& c : line_points)
  {
    // Ignore the first element of the line, since it will contain the creature that's
    // actually firing the missile.
    if (c == creature_coords)
    {
      continue;
    }

    tile = current_map->at(c);

    if (tile != nullptr && tile->has_creature())
    {
      CreaturePtr tile_creature = tile->get_creature();

      if (tile_creature != nullptr)
      {
        // There's a creature here - use this tile for targetting/dropping ammo,
        // if the corresponding check fails.
        pct_chance_fire_through = ctnc->calculate_pct_chance_pass_through_untargetted_square(firing_creature, tile_creature);

        if (!RNG::percent_chance(pct_chance_fire_through))
        {
          actual_coordinates.push_back(c);
          break;
        }
      }
    }
    // Check to see if there's a blocking feature, or if the tile itself blocks things
    // (walls, etc).
    else if (tile && ((tile->get_movement_multiplier() == 0) || (tile->has_blocking_feature())))
    {
      // Done - don't consider any other tiles.  Use the previous for dropping ammo.
      break;
    }
    else
    {
      // Update the target coordinates to the current tile's.
      actual_coordinates.push_back(c);
    }
  }

  return actual_coordinates;
}

bool RangedCombatUtils::is_coord_in_range(const Coordinate& c, MapPtr view_map)
{
  bool in_range = false;

  if (view_map != nullptr)
  {
    TilePtr tile = view_map->at(c);

    if (tile)
    {
      // The selected coordinates mapped to a tile in the view map,
      // so the selected tile is in range.
      in_range = true;
    }
  }

  return in_range;
}
