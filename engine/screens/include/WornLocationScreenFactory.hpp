#pragma once
#include "WornLocationSelectionScreen.hpp"
#include "Display.hpp"

class WornLocationScreenFactory
{
  public:
    WornLocationSelectionScreen create_skin_screen(DisplayPtr display);
    WornLocationSelectionScreen create_weaving_screen(DisplayPtr display);
};

