#include "AnimationTranslator.hpp"
#include "BallShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<pair<Coordinate, TilePtr>>, Animation> BallShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<pair<Coordinate, TilePtr>> affected_coords_and_tiles;
  uint spell_range = spell.get_range();

  DisplayTile dt('*', static_cast<int>(spell.get_colour()));

  vector<Coordinate> prev_coords;
  vector<Coordinate> current_coords;
  MovementPath movement_path;
  prev_coords.push_back(caster_coord);

  // Set the row/column offset, to be used to calculate the increasing
  // blast radius.
  int offset = 1;
  TileMagicChecker tmc;

  for (uint i = 0; i < spell_range; i++)
  {
    // Generate the coordinates.
    for (int row = (caster_coord.first - offset); row <= (caster_coord.first + offset); row++)
    {
      // At the top/bottom, generate the entire row.
      // Otherwise, generate only the edges:
      //
      // ***
      // *@*
      // ***
      if ((row == (caster_coord.first - offset)) || (row == caster_coord.first + offset))
      {
        for (int col = (caster_coord.second - offset); col <= (caster_coord.second + offset); col++)
        {
          Coordinate ball_coord(row, col);
          TilePtr tile = map->at(ball_coord);

          if (tile && !tmc.does_tile_block_spell(tile, spell) && is_coordinate_adjacent_to_coordinate_in_previous_frame(ball_coord, prev_coords))
          {
            current_coords.push_back(ball_coord);
            affected_coords_and_tiles.push_back(make_pair(ball_coord, tile));
          }
        }
      }
      else
      {
        Coordinate west_coord(row, caster_coord.second - offset);
        Coordinate east_coord(row, caster_coord.second + offset);

        TilePtr west_tile = map->at(west_coord);
        TilePtr east_tile = map->at(east_coord);

        if (east_tile && !tmc.does_tile_block_spell(east_tile, spell) && is_coordinate_adjacent_to_coordinate_in_previous_frame(east_coord, prev_coords))
        {
          current_coords.push_back(east_coord);
          affected_coords_and_tiles.push_back(make_pair(east_coord, east_tile));
        }

        if (west_tile && !tmc.does_tile_block_spell(west_tile, spell) && is_coordinate_adjacent_to_coordinate_in_previous_frame(west_coord, prev_coords))
        {
          current_coords.push_back(west_coord);
          affected_coords_and_tiles.push_back(make_pair(west_coord, west_tile));
        }
      }
    }

    vector<pair<DisplayTile, Coordinate>> frame;
    for (const Coordinate& c : current_coords)
    {
      frame.push_back(make_pair(dt, c));
    }

    movement_path.push_back(frame);
    prev_coords = current_coords;
    current_coords.clear();

    // Update the row and column offset.
    offset++;
  }

  // Create the animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, affected_coords_and_tiles, movement_path);
}

