#include "AnimationTranslator.hpp"
#include "BallShapeProcessor.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MapTranslator.hpp"
#include "Setting.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

BallShapeProcessor::BallShapeProcessor(const bool inc_centre_tile)
: include_centre_tile(inc_centre_tile)
{
}

BallShapeProcessor::BallShapeProcessor()
: include_centre_tile(false)
{
}

pair<vector<pair<Coordinate, TilePtr>>, Animation> BallShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  pair<vector<pair<Coordinate, TilePtr>>, MovementPath> affected_coords_and_tiles = get_affected_coords_and_tiles(map, spell, caster_coord);

  // Create the animation.
  CreaturePtr caster = map->at(caster_coord)->get_creature();
  return create_affected_tiles_and_animation(caster, map, affected_coords_and_tiles.first, affected_coords_and_tiles.second);
}

pair<vector<pair<Coordinate, TilePtr>>, MovementPath> BallShapeProcessor::get_affected_coords_and_tiles(MapPtr map, const Spell& spell, const Coordinate& caster_coord, const bool use_tile_details)
{
  vector<pair<Coordinate, TilePtr>> affected_coords_and_tiles;
  uint spell_range = spell.get_range();
  Game& game = Game::instance();
  CurrentCreatureAbilities cca;
  ISeasonPtr season = game.get_current_world()->get_calendar().get_season();
  Settings& settings = game.get_settings_ref();
  CreaturePtr player = game.get_current_player();
  bool player_blind = !cca.can_see(player);
  pair<Colour, Colour> tod_overrides = TimeOfDay::get_time_of_day_colours(game.get_current_world()->get_calendar().get_date().get_time_of_day(), map->get_map_type() == MapType::MAP_TYPE_OVERWORLD, settings.get_setting_as_bool(Setting::SHADE_TERRAIN), settings.get_setting_as_bool(Setting::SHADE_CREATURES_AND_ITEMS));
  vector<Colour> scv = String::create_colour_vector_from_csv_string(map->get_property(MapProperties::MAP_PROPERTIES_SHIMMER_COLOURS));
  ShimmerColours shimmer_colours(scv);

  vector<Coordinate> prev_coords;
  vector<Coordinate> current_coords;
  MovementPath movement_path;
  prev_coords.push_back(caster_coord);

  // Set the row/column offset, to be used to calculate the increasing
  // blast radius.
  int offset = 1;
  TileMagicChecker tmc;

  if (include_centre_tile)
  {
    TilePtr caster_tile = map->at(caster_coord);
    current_coords.push_back(caster_coord);
    affected_coords_and_tiles.push_back(make_pair(caster_coord, caster_tile));
  }

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
      Symbol s('*', spell.get_colour(), { SpritesheetIndex::SPRITESHEET_INDEX_SYSTEM, SpritesheetReference::SPRITESHEET_REFERENCE_MAGIC_BLAST });
      DisplayTile dt(s);

      if (use_tile_details)
      {
        TilePtr engine_tile = map->at(c);
        TilePtr fov_tile = player ? player->get_decision_strategy()->get_fov_map()->at(c) : nullptr;

        if (engine_tile != nullptr)
        {
          dt = MapTranslator::create_display_tile(player_blind, false, tod_overrides, shimmer_colours, engine_tile, fov_tile);
          dt.set_season(season->get_season());
        }
      }

      frame.push_back(make_pair(dt, c));
    }

    movement_path.push_back(frame);
    prev_coords = current_coords;
    current_coords.clear();

    // Update the row and column offset.
    offset++;
  }

  return make_pair(affected_coords_and_tiles, movement_path);
}