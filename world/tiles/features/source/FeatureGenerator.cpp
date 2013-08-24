#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "Bench.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "EvilAltar.hpp"
#include "FirePillar.hpp"
#include "Fountain.hpp"
#include "Gate.hpp"
#include "GoodAltar.hpp"
#include "NeutralAltar.hpp"
#include "Pew.hpp"

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
      altar = boost::make_shared<EvilAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      altar = boost::make_shared<NeutralAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_GOOD:
    default:
      altar = boost::make_shared<GoodAltar>(deity_id);
      break;    
  }
  
  return altar;
}

// Generate a door based on the parameters provided.
DoorPtr FeatureGenerator::generate_door()
{
  LockPtr lock_info;
  EntranceState door_state;
  DoorPtr door = boost::make_shared<Door>(lock_info, door_state);
  return door;
}

// Generate a gate
FeaturePtr FeatureGenerator::generate_gate()
{
  LockPtr lock_info;
  EntranceState gate_state;
  FeaturePtr gate = boost::make_shared<Gate>(lock_info, gate_state);
  return gate;
}

// Generate a fire pillar
FeaturePtr FeatureGenerator::generate_fire_pillar()
{
  FeaturePtr fire_pillar = boost::make_shared<FirePillar>();
  return fire_pillar;
}

// Generate a happy, bubbly fountain
FeaturePtr FeatureGenerator::generate_fountain()
{
  FeaturePtr fountain = boost::make_shared<Fountain>();
  return fountain;
}

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew(const PewDirection pew_direction)
{
  FeaturePtr pew;
  
  switch(pew_direction)
  {
    case PEW_DIRECTION_NORTH_SOUTH:
      pew = boost::make_shared<Pew>();
      break;
    case PEW_DIRECTION_EAST_WEST:
    default:
      pew = boost::make_shared<EastWestPew>();
      break;
  }

  return pew;
}

// Generate a wrought-iron bench
FeaturePtr FeatureGenerator::generate_bench()
{
  FeaturePtr bench = boost::make_shared<Bench>();
  return bench;
}

// Generate a sarcophagus
SarcophagusPtr FeatureGenerator::generate_sarcophagus(const MaterialType material_type)
{
  SarcophagusPtr sarcophagus = boost::make_shared<Sarcophagus>(material_type);

  return sarcophagus;
}