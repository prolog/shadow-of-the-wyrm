#pragma once
#include "Map.hpp"

// Interface class describing a pillar generator.  These generators,
// when given a map and a particular X-Y coordinate, blindly attempt to
// generate the pillar on that spot and the surrounding area, overwriting
// anything present.
class IPillarGenerator
{
  public:
    virtual int get_height() const = 0;
    virtual int get_width() const = 0;

    virtual void generate(MapPtr map, const int y_topleft, const int x_topleft);
};

