#pragma once
#include <boost/shared_ptr.hpp>
#include "Map.hpp"

class FieldOfViewStrategy
{
  public:
    virtual MapPtr calculate(MapPtr view_map) = 0;
};

typedef boost::shared_ptr<FieldOfViewStrategy> FieldOfViewStrategyPtr;
