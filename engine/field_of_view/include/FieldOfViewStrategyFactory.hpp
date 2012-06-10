#pragma once
#include "FieldOfViewTypes.hpp"
#include "FieldOfViewStrategy.hpp"

class FieldOfViewStrategyFactory
{
  public:
    static FieldOfViewStrategyPtr create_field_of_view_strategy(const FieldOfViewAlgorithmType type);

  protected:
    FieldOfViewStrategyFactory();
    ~FieldOfViewStrategyFactory();
};
