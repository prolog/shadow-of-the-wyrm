#pragma once
#include "Map.hpp"

class ViewMapTranslator
{
  public:
    static MapPtr create_view_map_around_tile(MapPtr original_map, const Coordinate& centre, const uint size);

  protected:
    ViewMapTranslator();
    ~ViewMapTranslator();
};
