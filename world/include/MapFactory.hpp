#pragma once
#include "Map.hpp"

class MapFactory
{
  public:
    static MapPtr create_map();

  protected:
    MapFactory();
    ~MapFactory();
};

