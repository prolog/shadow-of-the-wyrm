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

  BOOST_FOREACH(const Coordinate& c, movement_path)
  {
    TilePtr game_tile = current_map->at(c);
    TilePtr fov_tile = fov_map->at(c);

    DisplayTile previously_displayed = MapTranslator::create_display_tile(game_tile, fov_tile);
    previously_displayed.set_season(current_season);
    
    // Show the projectile.
    AnimationInstructionPtr instr = animation_factory->create_draw_instruction(c, projectile);
    animation.add_animation_instruction(instr);

    // Pause briefly.
    instr = animation_factory->create_pause_instruction();
    animation.add_animation_instruction(instr);

    // Re-draw what was there before the projectile was drawn.
    instr = animation_factory->create_draw_instruction(c, previously_displayed);
    animation.add_animation_instruction(instr);
  }

  return animation;
}
