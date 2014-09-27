#include "IFeatureManipulatorFactory.hpp"
#include "DefaultFeatureManipulator.hpp"
#include "PewFeatureManipulator.hpp"
#include "GoodAltarManipulator.hpp"
#include "NeutralAltarManipulator.hpp"
#include "EvilAltarManipulator.hpp"
#include "DoorGateManipulator.hpp"

IFeatureManipulatorPtr IFeatureManipulatorFactory::create_manipulator(const ClassIdentifier class_id)
{
  IFeatureManipulatorPtr manipulator;

  if (class_id == CLASS_ID_PEW)
  {
    manipulator = std::make_shared<PewFeatureManipulator>();
  }
  else if (class_id == CLASS_ID_GOOD_ALTAR)
  {
    manipulator = std::make_shared<GoodAltarManipulator>();
  }
  else if (class_id == CLASS_ID_NEUTRAL_ALTAR)
  {
    manipulator = std::make_shared<NeutralAltarManipulator>();
  }
  else if (class_id == CLASS_ID_EVIL_ALTAR)
  {
    manipulator = std::make_shared<EvilAltarManipulator>();
  }
  else if (class_id == CLASS_ID_DOOR || class_id == CLASS_ID_GATE)
  {
    manipulator = std::make_shared<DoorGateManipulator>();
  }
  // All other features
  else
  {
    manipulator = std::make_shared<DefaultFeatureManipulator>();
  }

  return manipulator;
}
