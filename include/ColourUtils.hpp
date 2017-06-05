#pragma once
#include "Colours.hpp"

class ColourUtils
{
  public:
    static Colour get_alternate_hue(const Colour c);

  protected:
    ColourUtils();
    ~ColourUtils();

    static const int COLOUR_BOLD_OFFSET;
};

