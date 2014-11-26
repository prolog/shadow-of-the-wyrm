#include "FeatureGenerator.hpp"
#include "Bench.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "EvilAltar.hpp"
#include "FirePillar.hpp"
#include "Fountain.hpp"
#include "Forge.hpp"
#include "Gate.hpp"
#include "GoodAltar.hpp"
#include "JewelerWorkbench.hpp"
#include "NeutralAltar.hpp"
#include "Pew.hpp"
#include "Tannery.hpp"
#include "WheelAndLoom.hpp"

FeatureGenerator::FeatureGenerator()
{
}

FeatureGenerator::~FeatureGenerator()
{
}

// Generates an altar based on the alignment and provided deity ID.
FeaturePtr FeatureGenerator::generate_altar(const std::string& deity_id, const AlignmentRange alignment)
{
  FeaturePtr altar;
  
  switch(alignment)
  {
    case ALIGNMENT_RANGE_EVIL:
      altar = std::make_shared<EvilAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      altar = std::make_shared<NeutralAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_GOOD:
    default:
      altar = std::make_shared<GoodAltar>(deity_id);
      break;    
  }
  
  return altar;
}

// Generate a door based on the parameters provided.
DoorPtr FeatureGenerator::generate_door()
{
  LockPtr lock_info;
  EntranceState door_state;
  DoorPtr door = std::make_shared<Door>(lock_info, door_state);
  return door;
}

// Generate a gate
FeaturePtr FeatureGenerator::generate_gate()
{
  LockPtr lock_info;
  EntranceState gate_state;
  FeaturePtr gate = std::make_shared<Gate>(lock_info, gate_state);
  return gate;
}

// Generate a fire pillar
FeaturePtr FeatureGenerator::generate_fire_pillar()
{
  FeaturePtr fire_pillar = std::make_shared<FirePillar>();
  return fire_pillar;
}

// Generate a happy, bubbly fountain
FeaturePtr FeatureGenerator::generate_fountain()
{
  FeaturePtr fountain = std::make_shared<Fountain>();
  return fountain;
}

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew(const PewDirection pew_direction)
{
  FeaturePtr pew;
  
  switch(pew_direction)
  {
    case PEW_DIRECTION_NORTH_SOUTH:
      pew = std::make_shared<Pew>();
      break;
    case PEW_DIRECTION_EAST_WEST:
    default:
      pew = std::make_shared<EastWestPew>();
      break;
  }

  return pew;
}

// Generate a wrought-iron bench
FeaturePtr FeatureGenerator::generate_bench()
{
  FeaturePtr bench = std::make_shared<Bench>();
  return bench;
}

// Generate a sarcophagus
SarcophagusPtr FeatureGenerator::generate_sarcophagus(const MaterialType material_type)
{
  SarcophagusPtr sarcophagus = std::make_shared<Sarcophagus>(material_type);

  return sarcophagus;
}

// Generate a forge
FeaturePtr FeatureGenerator::generate_forge()
{
  FeaturePtr forge = std::make_shared<Forge>();
  return forge;
}

// Generate a tannery
FeaturePtr FeatureGenerator::generate_tannery()
{
  FeaturePtr tannery = std::make_shared<Tannery>();
  return tannery;
}

// Generate a jeweler's workbench
FeaturePtr FeatureGenerator::generate_jeweler_workbench()
{
  FeaturePtr workbench = std::make_shared<JewelerWorkbench>();
  return workbench;
}

// Generate spinning wheel and loom
FeaturePtr FeatureGenerator::generate_wheel_and_loom()
{
  FeaturePtr wheel_and_loom = std::make_shared<WheelAndLoom>();
  return wheel_and_loom;
}