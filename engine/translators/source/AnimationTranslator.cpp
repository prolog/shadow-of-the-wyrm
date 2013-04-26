#include <boost/foreach.hpp>
#include "AnimationTranslator.hpp"
#include "MapTranslator.hpp"

using namespace std;

// Use the given display to create an animation factory that this
// translator will use to create its animations.
AnimationTranslator::AnimationTranslator(DisplayPtr display)
{
  animation_factory = display->create_animation_factory();
}

Animation AnimationTranslator::create_movement_animation(const DisplayTile& projectile, const Season current_season, const vector<vector<Coordinate> >& movement_path, const bool redraw_previous_frame, MapPtr current_map, MapPtr fov_map)
{
  Animation animation;

  uint num_steps = movement_path.size();

  for (uint i = 0; i < num_steps; i++)
  {
    vector<Coordinate> current_frame = movement_path.at(i);
    vector<AnimationInstructionPtr> coords_in_frame;
    vector<AnimationInstructionPtr> frame_cleanup;

    BOOST_FOREACH(Coordinate c, current_frame)
    {
      TilePtr game_tile = current_map->at(c);
      TilePtr fov_tile = fov_map->at(c);

      // Guard against a range outside the FOV/map.
      if (!game_tile || !fov_tile) continue;

      DisplayTile previously_displayed = MapTranslator::create_display_tile(game_tile, fov_tile);
      previously_displayed.set_season(current_season);
    
      // Add the updated coordinate value to the in-frame list.
      AnimationInstructionPtr instr = animation_factory->create_draw_instruction(c, projectile);
      coords_in_frame.push_back(instr);

      // Add the previous coordinate value to the cleanup list.
      instr = animation_factory->create_draw_instruction(c, previously_displayed);
      frame_cleanup.push_back(instr);
    }

    // Add the updated coordinates to the animation.
    BOOST_FOREACH(AnimationInstructionPtr instr, coords_in_frame)
    {
      animation.add_animation_instruction(instr);
    }

    // Only pause and then redraw what was previously there if we're not at the end
    // of the path.  This prevents the last tile from "blinking".
    if (i != num_steps-1)
    {
      // Pause briefly.
      AnimationInstructionPtr instr = animation_factory->create_pause_instruction();
      animation.add_animation_instruction(instr);

      if (redraw_previous_frame)
      {
        BOOST_FOREACH(AnimationInstructionPtr instr, frame_cleanup)
        {
          animation.add_animation_instruction(instr);
        }
      }
    }
  }

  return animation;
}
