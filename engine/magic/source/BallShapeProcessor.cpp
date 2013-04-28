#include "AnimationTranslator.hpp"
#include "BallShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<TilePtr>, Animation> BallShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  uint spell_range = spell.get_range();

  DisplayTile dt('*', spell.get_colour());

  vector<Coordinate> prev_coords;
  vector<Coordinate> current_coords;
  vector<pair<DisplayTile, vector<Coordinate>>> movement_path;
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

          if (tile && !tmc.does_tile_block_spell(tile) && is_coordinate_adjacent_to_coordinate_in_previous_frame(ball_coord, prev_coords))
          {
            current_coords.push_back(ball_coord);
            affected_tiles.push_back(tile);
          }
        }
      }
      else
      {
        Coordinate west_coord(row, caster_coord.second - offset);
        Coordinate east_coord(row, caster_coord.second + offset);

        TilePtr west_tile = map->at(west_coord);
        TilePtr east_tile = map->at(east_coord);

        if (east_tile && !tmc.does_tile_block_spell(east_tile) && is_coordinate_adjacent_to_coordinate_in_previous_frame(east_coord, prev_coords))
        {
          current_coords.push_back(east_coord);
          affected_tiles.push_back(east_tile);
        }

        if (west_tile && !tmc.does_tile_block_spell(west_tile) && is_coordinate_adjacent_to_coordinate_in_previous_frame(west_coord, prev_coords))
        {
          current_coords.push_back(west_coord);
          affected_tiles.push_back(west_tile);
        }
      }
    }

    movement_path.push_back(make_pair(dt, current_coords));
    prev_coords = current_coords;
    current_coords.clear();

    // Update the row and column offset.
    offset++;
  }

  // Create the animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  MapPtr fov_map = caster->get_decision_strategy()->get_fov_map();
  Game& game = Game::instance();
  AnimationTranslator at(game.get_display());

  Animation ball_animation = at.create_movement_animation(game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, map, fov_map);
  pair<vector<TilePtr>, Animation> affected_tiles_and_animation(affected_tiles, ball_animation);
  return affected_tiles_and_animation;
}

