#pragma once
#include "FeatureManipulator.hpp"

class IFeatureManipulatorFactory
{
  public:
    FeatureManipulatorPtr static create_manipulator(FeaturePtr feature);

  protected:
    IFeatureManipulatorFactory() {};
    ~IFeatureManipulatorFactory() {};
};

