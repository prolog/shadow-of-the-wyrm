#include "IFeatureManipulatorFactory.hpp"
#include "DefaultFeatureManipulator.hpp"
#include "PewFeatureManipulator.hpp"

IFeatureManipulatorPtr IFeatureManipulatorFactory::create_manipulator(const ClassIdentifier class_id)
{
  IFeatureManipulatorPtr manipulator;

  if (class_id == CLASS_ID_PEW)
  {
    manipulator = std::make_shared<PewFeatureManipulator>();
  }
  // All other features
  else
  {
    manipulator = std::make_shared<DefaultFeatureManipulator>();
  }

  return manipulator;
}
