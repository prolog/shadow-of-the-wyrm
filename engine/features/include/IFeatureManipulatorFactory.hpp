#pragma once
#include "IFeatureManipulator.hpp"

class IFeatureManipulatorFactory
{
  public:
    IFeatureManipulatorPtr static create_manipulator(const ClassIdentifier class_id);

  protected:
    IFeatureManipulatorFactory() {};
    ~IFeatureManipulatorFactory() {};
};

