#pragma once
#include "IFeatureManipulator.hpp"

class IFeatureManipulatorFactory
{
  public:
    IFeatureManipulatorPtr static create_manipulator(FeaturePtr feature);

  protected:
    IFeatureManipulatorFactory() {};
    ~IFeatureManipulatorFactory() {};
};

