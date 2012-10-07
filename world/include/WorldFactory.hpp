#pragma once
#include "World.hpp"

class WorldFactory
{
  public:
    static WorldPtr create_world();

  protected:
    WorldFactory();
    ~WorldFactory();
};

