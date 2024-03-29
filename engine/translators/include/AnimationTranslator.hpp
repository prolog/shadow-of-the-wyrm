#pragma once
#include "Animation.hpp"
#include "Display.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "MapMovementTypes.hpp"

class AnimationTranslator
{
  public:
    AnimationTranslator(DisplayPtr display);

    Animation create_movement_animation(CreaturePtr creature, const bool player_blinded, const Season current_season, const MovementPath& movement_path, const bool redraw_previous_frame, MapPtr current_map, MapPtr creature_fov_map);

  protected:
    AnimationFactoryPtr animation_factory;
};

