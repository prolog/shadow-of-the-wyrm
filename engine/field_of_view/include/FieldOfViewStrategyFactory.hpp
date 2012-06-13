#pragma once
#include "FieldOfViewTypes.hpp"
#include "FieldOfViewStrategy.hpp"

class FieldOfViewStrategyFactory
{
  public:
    static FieldOfViewStrategyPtr create_field_of_view_strategy(const bool set_view_property_on_fov_tiles, const FieldOfViewAlgorithmType type = FOV_RAY_CASTING);

  protected:
    FieldOfViewStrategyFactory();
    ~FieldOfViewStrategyFactory();
};
