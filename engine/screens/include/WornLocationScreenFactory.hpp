#pragma once
#include "WornLocationSelectionScreen.hpp"
#include "Display.hpp"

class WornLocationScreenFactory
{
  public:
    WornLocationSelectionScreenPtr create_skin_screen(DisplayPtr display);
    WornLocationSelectionScreenPtr create_weaving_screen(DisplayPtr display);
};

