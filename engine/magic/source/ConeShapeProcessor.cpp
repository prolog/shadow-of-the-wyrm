#include "ConeShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "DisplayTile.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

// Create a cone-shaped spell of the form:
//    *
//   **
// @***
//   **
//    *
//
// Cone-shaped spells have the restriction that they only accept a 
// cardinal direction.
pair<vector<TilePtr>, Animation> ConeShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  int frontier_size = 0;
  uint spell_range = spell.get_range();

  DisplayTile dt('*', static_cast<int>(spell.get_colour()));

  Coordinate prev_coord = caster_coord;
  vector<Coordinate> previous_frame;
  previous_frame.push_back(caster_coord);

  vector<Coordinate> current_frame;

  MovementPath movement_path;
  TileMagicChecker tmc;
  vector<TilePtr> affected_tiles;

  Coordinate centre_coord = CoordUtils::get_new_coordinate(prev_coord, d);

  for (uint i = 0; i < spell_range; i++)
  {
    // N, S
    if (d == Direction::DIRECTION_NORTH || d == Direction::DIRECTION_SOUTH)
    {
      for (int col = (centre_coord.second - frontier_size); col <= (centre_coord.second + frontier_size); col++)
      {
        Coordinate c(centre_coord.first, col);
        TilePtr tile = map->at(c);

        if (tile && !tmc.does_tile_block_spell(tile) && is_coordinate_adjacent_to_coordinate_in_previous_frame(c, previous_frame))
        {
          current_frame.push_back(c);
          affected_tiles.push_back(tile);
        }
      }
    }
    // E, W
    else if (d == Direction::DIRECTION_EAST || d == Direction::DIRECTION_WEST)
    {
      for (int row = (centre_coord.first - frontier_size); row <= (centre_coord.first + frontier_size); row++)
      {
        Coordinate c(row, centre_coord.second);
        TilePtr tile = map->at(c);

        if (tile && !tmc.does_tile_block_spell(tile) && is_coordinate_adjacent_to_coordinate_in_previous_frame(c, previous_frame))
        {
          current_frame.push_back(c);
          affected_tiles.push_back(tile);
        }
      }
    }
    // Self-targetting
    else if (d == Direction::DIRECTION_NULL)
    {
      current_frame.push_back(centre_coord);

      TilePtr tile = map->at(centre_coord);
      affected_tiles.push_back(tile);
    }

    // Update the frames required for the animation.
    vector<pair<DisplayTile, Coordinate>> frame;

    for (const Coordinate& c : current_frame)
    {
      frame.push_back(make_pair(dt, c));
    }

    movement_path.push_back(frame);
    previous_frame = current_frame;
    current_frame.clear();

    // Update the centre for the next row or column.
    centre_coord = CoordUtils::get_new_coordinate(centre_coord, d);

    // Increase the size of the next frame, and update the offset.
    frontier_size++;
  }

  // Create the animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, affected_tiles, movement_path);
}

