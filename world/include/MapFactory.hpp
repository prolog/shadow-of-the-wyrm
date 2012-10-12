#pragma once
#include "Map.hpp"

class MapFactory
{
  public:
    static MapPtr create_map();
    static MapExitPtr create_map_exit();

  protected:
    MapFactory();
    ~MapFactory();
};

