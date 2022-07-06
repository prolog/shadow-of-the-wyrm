#include "AnimationTranslator.hpp"
#include "Conversion.hpp"
#include "Date.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MapTranslator.hpp"
#include "MapUtils.hpp"
#include "Setting.hpp"

using namespace std;

// Use the given display to create an animation factory that this
// translator will use to create its animations.
AnimationTranslator::AnimationTranslator(DisplayPtr display)
{
  animation_factory = display->create_animation_factory();
}

Animation AnimationTranslator::create_movement_animation(const bool player_blinded, const Season current_season, const MovementPath& movement_path, const bool redraw_previous_frame, MapPtr current_map, MapPtr fov_map)
{
  Animation animation;

  if (player_blinded || animation_factory == nullptr)
  {
    return animation;
  }

  uint num_steps = movement_path.size();
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  Calendar& calendar = game.get_current_world()->get_calendar();
  Settings& settings = game.get_settings_ref();
  pair<Colour, Colour> tod_overrides = TimeOfDay::get_time_of_day_colours(calendar.get_date().get_time_of_day(), MapUtils::get_supports_time_of_day(map->get_map_type()), settings.get_setting_as_bool(Setting::SHADE_TERRAIN), settings.get_setting_as_bool(Setting::SHADE_CREATURES_AND_ITEMS));
  vector<Colour> scv = String::create_colour_vector_from_csv_string(map->get_property(MapProperties::MAP_PROPERTIES_SHIMMER_COLOURS));
  ShimmerColours shimmer_colours(scv);

  for (uint i = 0; i < num_steps; i++)
  {
    vector<pair<DisplayTile, Coordinate>> current_frame = movement_path.at(i);
    vector<AnimationInstructionPtr> coords_in_frame;
    vector<AnimationInstructionPtr> frame_cleanup;

    for (const pair<DisplayTile, Coordinate>& dt_c_pair : current_frame)
    {
      DisplayTile projectile = dt_c_pair.first;
      Coordinate c = dt_c_pair.second;

      // Sanity check: ensure both maps are valid before trying to proceed.
      if (current_map == nullptr || fov_map == nullptr)
      {
        break;
      }

      TilePtr game_tile = current_map->at(c);
      TilePtr fov_tile = fov_map->at(c);

      // Guard against a range outside the FOV/map.
      if (!game_tile || !fov_tile) continue;

      DisplayTile previously_displayed = MapTranslator::create_display_tile(player_blinded, false, tod_overrides, shimmer_colours, game_tile, fov_tile, c.first, c.second);
      previously_displayed.set_season(current_season);
    
      // Add the updated coordinate value to the in-frame list.
      AnimationInstructionPtr instr = animation_factory->create_draw_instruction(c, projectile);
      coords_in_frame.push_back(instr);

      // Add the previous coordinate value to the cleanup list.
      instr = animation_factory->create_draw_instruction(c, previously_displayed);
      frame_cleanup.push_back(instr);
    }

    // Add the updated coordinates to the animation.
    for (AnimationInstructionPtr& instr : coords_in_frame)
    {
      animation.add_animation_instruction(instr);
    }

    // Only pause and then redraw what was previously there if we're not at the end
    // of the path.  This prevents the last tile from "blinking".
    if (i != num_steps-1)
    {
      // Pause briefly.
      AnimationInstructionPtr instr = animation_factory->create_pause_instruction();
      animation.add_animation_instruction(std::move(instr));

      if (redraw_previous_frame)
      {
        for (AnimationInstructionPtr& instr : frame_cleanup)
        {
          animation.add_animation_instruction(instr);
        }
      }
    }
  }

  return animation;
}
