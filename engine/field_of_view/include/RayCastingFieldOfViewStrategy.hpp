#pragma once
#include "FieldOfViewStrategy.hpp"

class RayCastingFieldOfViewStrategy : public FieldOfViewStrategy
{
  public:
    MapPtr calculate(MapPtr view_map);
};
