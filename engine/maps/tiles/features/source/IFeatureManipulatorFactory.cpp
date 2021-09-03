#include "IFeatureManipulatorFactory.hpp"
#include "DefaultFeatureManipulator.hpp"
#include "FenceManipulator.hpp"
#include "ForgeManipulator.hpp"
#include "PewManipulator.hpp"
#include "GoodAltarManipulator.hpp"
#include "NeutralAltarManipulator.hpp"
#include "EvilAltarManipulator.hpp"
#include "DoorGateManipulator.hpp"
#include "BarrelManipulator.hpp"
#include "JewelerWorkbenchManipulator.hpp"
#include "KilnManipulator.hpp"
#include "PulperManipulator.hpp"
#include "SarcophagusManipulator.hpp"
#include "SlotMachineManipulator.hpp"
#include "TableManipulator.hpp"
#include "TanneryManipulator.hpp"
#include "TrapManipulator.hpp"
#include "WheelAndLoomManipulator.hpp"

FeatureManipulatorPtr IFeatureManipulatorFactory::create_manipulator(FeaturePtr feature)
{
  FeatureManipulatorPtr manipulator;

  if (feature != nullptr)
  {
    ClassIdentifier class_id = feature->get_class_identifier();

    if (class_id == ClassIdentifier::CLASS_ID_PEW)
    {
      manipulator = std::make_unique<PewManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_GOOD_ALTAR)
    {
      manipulator = std::make_unique<GoodAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR)
    {
      manipulator = std::make_unique<NeutralAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_EVIL_ALTAR)
    {
      manipulator = std::make_unique<EvilAltarManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_DOOR || class_id == ClassIdentifier::CLASS_ID_GATE)
    {
      manipulator = std::make_unique<DoorGateManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_BARREL)
    {
      manipulator = std::make_unique<BarrelManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_FORGE)
    {
      manipulator = std::make_unique<ForgeManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH)
    {
      manipulator = std::make_unique<JewelerWorkbenchManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_TANNERY)
    {
      manipulator = std::make_unique<TanneryManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM)
    {
      manipulator = std::make_unique<WheelAndLoomManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_TRAP)
    {
      manipulator = std::make_unique<TrapManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_SARCOPHAGUS)
    {
      manipulator = std::make_unique<SarcophagusManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_TABLE)
    {
      manipulator = std::make_unique<TableManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_SLOT_MACHINE)
    {
      manipulator = std::make_unique<SlotMachineManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_PULPER)
    {
      manipulator = std::make_unique<PulperManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_KILN)
    {
      manipulator = std::make_unique<KilnManipulator>(feature);
    }
    else if (class_id == ClassIdentifier::CLASS_ID_FENCE)
    {
      manipulator = std::make_unique<FenceManipulator>(feature);
    }
    // All other features
    else
    {
      manipulator = std::make_unique<DefaultFeatureManipulator>(feature);
    }
  }

  return manipulator;
}
