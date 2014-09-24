#include "IFeatureManipulatorFactory.hpp"
#include "DefaultFeatureManipulator.hpp"

IFeatureManipulatorPtr IFeatureManipulatorFactory::create_manipulator(const ClassIdentifier class_id)
{
  IFeatureManipulatorPtr manipulator = std::make_shared<DefaultFeatureManipulator>();

  return manipulator;
}
