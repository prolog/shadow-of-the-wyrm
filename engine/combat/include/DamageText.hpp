#pragma once
#include "Colours.hpp"
#include "Creature.hpp"

class DamageText
{
  public:
    Colour get_colour(CreaturePtr creature) const;

  protected:
    static const float PCT_PLAYER_HP_COLOUR_CHANGE;
};
