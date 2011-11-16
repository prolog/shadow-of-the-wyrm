#pragma once
#include "Map.hpp"
#include "Directions.hpp"

#define DEFAULT_ROAD_WIDTH 3

class RoadGenerator
{
  public:
    RoadGenerator(const int width=DEFAULT_ROAD_WIDTH);
    RoadGenerator(const CardinalDirection direction, const int width=DEFAULT_ROAD_WIDTH);

    virtual MapPtr generate(MapPtr map);

  protected:
    void generate_road(MapPtr map);

    const int ROAD_WIDTH;
    const CardinalDirection ROAD_DIRECTION;
};
