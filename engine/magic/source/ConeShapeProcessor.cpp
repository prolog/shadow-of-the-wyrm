#include "AnimationTranslator.hpp"
#include "ConeShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
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

  Coordinate prev_coord = caster_coord;
  vector<Coordinate> previous_frame;
  previous_frame.push_back(caster_coord);

  vector<Coordinate> current_frame;

  vector<vector<Coordinate>> movement_path;

  TileMagicChecker tmc;

  vector<TilePtr> affected_tiles;

  Coordinate centre_coord = CoordUtils::get_new_coordinate(prev_coord, d);

  for (uint i = 0; i < spell_range; i++)
  {
    // N, S
    if (d == DIRECTION_NORTH || d == DIRECTION_SOUTH)
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
    else if (d == DIRECTION_EAST || d == DIRECTION_WEST)
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

    // Update the frames required for the animation.
    movement_path.push_back(current_frame);
    previous_frame = current_frame;
    current_frame.clear();

    // Update the centre for the next row or column.
    centre_coord = CoordUtils::get_new_coordinate(centre_coord, d);

    // Increase the size of the next frame, and update the offset.
    frontier_size++;
  }

  // Create the animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  MapPtr fov_map = caster->get_decision_strategy()->get_fov_map();
  DisplayTile dt('*', spell.get_colour());
  Game& game = Game::instance();
  AnimationTranslator at(game.get_display());

  Animation cone_animation = at.create_movement_animation(dt, game.get_current_world()->get_calendar().get_season()->get_season(), movement_path, false, map, fov_map);
  pair<vector<TilePtr>, Animation> affected_tiles_and_animation(affected_tiles, cone_animation);
  return affected_tiles_and_animation;
}

