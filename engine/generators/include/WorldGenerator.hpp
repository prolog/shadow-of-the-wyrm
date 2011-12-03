#pragma once
#include <map>
#include "Generator.hpp"

// JCD FIXME: Eventually, set about changing all the "MapPtr" arguments to "const MapPtr&" arguments.

class WorldGenerator : public Generator
{
  public:
    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual MapPtr generate_set_islands_and_continents(MapPtr map);
    virtual MapPtr generate_random_islands(MapPtr map);

    void generate_little_island(MapPtr map);
    void generate_far_reaches(MapPtr map);
};
