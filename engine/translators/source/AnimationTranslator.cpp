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

Animation AnimationTranslator::create_movement_animation(const DisplayTile& projectile, const Season current_season, const vector<Coordinate>& movement_path, MapPtr current_map, MapPtr fov_map)
{
  Animation animation;

  uint num_steps = movement_path.size();

  for (uint i = 0; i < num_steps; i++)
  {
    Coordinate c = movement_path.at(i);
    TilePtr game_tile = current_map->at(c);
    TilePtr fov_tile = fov_map->at(c);

    // Guard against a range outside the FOV/map.
    if (!game_tile || !fov_tile) continue;

    DisplayTile previously_displayed = MapTranslator::create_display_tile(game_tile, fov_tile);
    previously_displayed.set_season(current_season);
    
    // Show the projectile.
    AnimationInstructionPtr instr = animation_factory->create_draw_instruction(c, projectile);
    animation.add_animation_instruction(instr);

    // Only pause and then redraw what was previously there if we're not at the end
    // of the path.  This prevents the last tile from "blinking".
    if (i != num_steps-1)
    {
      // Pause briefly.
      instr = animation_factory->create_pause_instruction();
      animation.add_animation_instruction(instr);

      // Re-draw what was there before the projectile was drawn.
      instr = animation_factory->create_draw_instruction(c, previously_displayed);
      animation.add_animation_instruction(instr);
    }
  }

  return animation;
}
