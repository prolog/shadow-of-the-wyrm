#include "IFeatureManipulatorFactory.hpp"
#include "DefaultFeatureManipulator.hpp"
#include "ForgeManipulator.hpp"
#include "PewManipulator.hpp"
#include "GoodAltarManipulator.hpp"
#include "NeutralAltarManipulator.hpp"
#include "EvilAltarManipulator.hpp"
#include "DoorGateManipulator.hpp"
#include "BarrelManipulator.hpp"
#include "JewelerWorkbenchManipulator.hpp"
#include "TanneryManipulator.hpp"
#include "TrapManipulator.hpp"
#include "WheelAndLoomManipulator.hpp"

IFeatureManipulatorPtr IFeatureManipulatorFactory::create_manipulator(FeaturePtr feature)
{
  IFeatureManipulatorPtr manipulator;

  if (feature != nullptr)
  {
    ClassIdentifier class_id = feature->get_class_identifier();

    if (class_id == ClassIdentifier::CLASS_ID_PEW)
    {
      manipulator = std::make_shared<PewManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_GOOD_ALTAR)
    {
      manipulator = std::make_shared<GoodAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR)
    {
      manipulator = std::make_shared<NeutralAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_EVIL_ALTAR)
    {
      manipulator = std::make_shared<EvilAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_DOOR || class_id == ClassIdentifier::CLASS_ID_GATE)
    {
      manipulator = std::make_shared<DoorGateManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_BARREL)
    {
      manipulator = std::make_shared<BarrelManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_FORGE)
    {
      manipulator = std::make_shared<ForgeManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH)
    {
      manipulator = std::make_shared<JewelerWorkbenchManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_TANNERY)
    {
      manipulator = std::make_shared<TanneryManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM)
    {
      manipulator = std::make_shared<WheelAndLoomManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_TRAP)
    {
      manipulator = std::make_shared<TrapManipulator>(feature);
    }
    // All other features
    else
    {
      manipulator = std::make_shared<DefaultFeatureManipulator>(feature);
    }
  }

  return manipulator;
}
