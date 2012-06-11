#pragma once
#include <boost/shared_ptr.hpp>
#include "Map.hpp"

class FieldOfViewStrategy
{
  public:
    virtual MapPtr calculate(MapPtr view_map, const Coordinate& centre_coordinate, const int los_length) = 0;
    
  protected:
    void add_point_to_map(const Coordinate& c, MapPtr view_map, MapPtr fov_map);
};

typedef boost::shared_ptr<FieldOfViewStrategy> FieldOfViewStrategyPtr;
