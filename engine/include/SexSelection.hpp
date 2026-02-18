#pragma once
#include "CreatureFeatures.hpp"
#include "Display.hpp"

// Class that handles sex selection, if that option has been set. Displays
// both the regular sex selection screen as well as an info screen if the
// player wants to get more info on a particular sex.
class SexSelection
{
  public:
    void select_sex(DisplayPtr display, CreatureSex& sex);
};
