#include <cmath>
#include "AnimationTranslator.hpp"
#include "BallShapeProcessor.hpp"
#include "StormShapeProcessor.hpp"
#include "ColourUtils.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MapTranslator.hpp"
#include "RNG.hpp"
#include "Setting.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

pair<vector<pair<Coordinate, TilePtr>>, Animation> StormShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  uint spell_range = spell.get_range();
  uint spell_radius = spell.get_shape().get_radius();
  uint num_tiles_affected = 0;

  // If this is a regular storm (no beams), select more tiles than if this is
  // a radiant storm with beams emanating from the selected points.
  if (spell_radius == 0)
  {
    num_tiles_affected = static_cast<uint>(pow(spell_range, 2));
  }
  else
  {
    num_tiles_affected = spell_range + (spell_range / 2);
  }

  vector<Coordinate> potential_coords = generate_potential_coords(map, caster_coord, spell);
  pair<vector<pair<Coordinate, TilePtr>>, MovementPath> storm_tiles_and_movement = get_storm_tiles_and_movement(map, spell, caster_coord, potential_coords, num_tiles_affected);

  // Create the storm animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, storm_tiles_and_movement.first, storm_tiles_and_movement.second);
}

// Generate all the potential coordinates - those in range with valid tiles,
// that are not the caster's tile.
vector<Coordinate> StormShapeProcessor::generate_potential_coords(MapPtr map, const Coordinate& caster_coord, const Spell& spell)
{
  vector<Coordinate> potential_coords;
  uint spell_range = spell.get_range();
  int si_spell_range = static_cast<int>(spell_range);
  TileMagicChecker tmc;

  // Generate the coordinates, leaving the caster safe.
  for (int row = (caster_coord.first - si_spell_range); row <= (caster_coord.first + si_spell_range); row++)
  {
    for (int col = (caster_coord.second - si_spell_range); col <= (caster_coord.second + si_spell_range); col++)
    {
      Coordinate storm_coord(row, col);
      TilePtr tile = map->at(storm_coord);

      if ((storm_coord != caster_coord) && tile != nullptr && !tmc.does_tile_block_spell(tile, spell))
      {
        potential_coords.push_back(storm_coord);
      }
    }
  }

  return potential_coords;
}

// Select a number of the potential coordinates for the spell, allowing
// duplicates.
pair<vector<pair<Coordinate, TilePtr>>, MovementPath> StormShapeProcessor::get_storm_tiles_and_movement(MapPtr map, const Spell& spell, const Coordinate& caster_coord, const vector<Coordinate>& coords, const uint num_tiles_affected)
{
  pair<vector<pair<Coordinate, TilePtr>>, MovementPath> result;

  size_t coords_size = coords.size();
  uint spell_radius = spell.get_shape().get_radius();
  Symbol s('*', spell.get_colour(), SpritesheetLocation(SpritesheetIndex::SPRITESHEET_INDEX_SYSTEM, SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST));  DisplayTile dt(s);

  Game& game = Game::instance();
  ISeasonPtr season = game.get_current_world()->get_calendar().get_season();
  CreaturePtr player = game.get_current_player();
  vector<Colour> scv = String::create_colour_vector_from_csv_string(map->get_property(MapProperties::MAP_PROPERTIES_SHIMMER_COLOURS));
  ShimmerColours shimmer_colours(scv);

  Spell mini_burst = spell;
  mini_burst.set_range(spell_radius);
  Colour burst_colour = mini_burst.get_colour();

  if (coords_size > 0)
  {
    for (uint i = 0; i < num_tiles_affected; i++)
    {
      stringstream ss;
      Coordinate rand_coord = coords.at(RNG::range(0, coords_size - 1));

      TilePtr tile = map->at(rand_coord);
      TilePtr fov_tile = player ? player->get_decision_strategy()->get_fov_map()->at(rand_coord) : nullptr;

      result.first.push_back(make_pair(rand_coord, tile));

      if (spell_radius == 0)
      {
        // Push back the selected coordinate (the eye of the mini-storm).
        result.second.push_back({ make_pair(dt, rand_coord) });
      }

      // If this is a radiant storm, calculate the balls created from the random
      // coordinate.  Ensure that the caster's coordinate is always excluded.
      //
      // We calculate two balls: one with the alternate hue, one with the regular
      // one, and then add them both to the movement path.  This allows the path
      // of any subsequent, overlapping balls to be easily seen.
      else if (spell_radius > 0)
      {
        BallShapeProcessor bsp(true);

        // Colour and whether to use the actual tile details in the ball,
        // rather than the spell symbols.
        vector<pair<Colour, bool>> colours = { {burst_colour, false},
                                             {ColourUtils::get_alternate_hue(burst_colour), false},
                                             {Colour::COLOUR_UNDEFINED, true} };
        bool add_tile_details = true;

        for (const auto& colour : colours)
        {
          mini_burst.set_colour(colour.first);
          auto ball_pair = bsp.get_affected_coords_and_tiles(map, mini_burst, rand_coord, colour.second);

          remove_caster_details_from_ball(ball_pair, caster_coord);

          // First time through the ball, add the affected coordinates and tiles.
          if (add_tile_details)
          {
            vector<pair<Coordinate, TilePtr>> affected = ball_pair.first;

            for (const auto& aff : affected)
            {
              result.first.push_back(aff);
            }

            add_tile_details = false;
          }

          // Push back the additional elements of the ball to the movement details.
          for (const auto& ball_movement_frame : ball_pair.second)
          {
            result.second.push_back(ball_movement_frame);
          }
        }
      }
    }
  }

  return result;
}

// When creating a radiant storm, the caster should always be excluded from any
// peripheral damage.
void StormShapeProcessor::remove_caster_details_from_ball(pair<vector<pair<Coordinate, TilePtr>>, MovementPath>& ball_pair, const Coordinate& caster_coord)
{
  vector<pair<Coordinate, TilePtr>>& ball_details = ball_pair.first;
  MovementPath& mp = ball_pair.second;

  auto new_end = std::remove_if(ball_details.begin(), ball_details.end(),
    [caster_coord](const pair<Coordinate, TilePtr>& coord_pair)
  {
    return coord_pair.first == caster_coord;
  });

  ball_details.erase(new_end, ball_details.end());

  for (auto& mp_vec : mp)
  {
    auto new_mp_end = std::remove_if(mp_vec.begin(), mp_vec.end(),
      [caster_coord](const pair<DisplayTile, Coordinate>& dc_pair)
    {
      return dc_pair.second == caster_coord;
    });

    mp_vec.erase(new_mp_end, mp_vec.end());
  }
}
