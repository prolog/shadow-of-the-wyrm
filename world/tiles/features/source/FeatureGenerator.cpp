#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "Bench.hpp"
#include "Door.hpp"
#include "EastWestPew.hpp"
#include "EvilAltar.hpp"
#include "FirePillar.hpp"
#include "Fountain.hpp"
#include "GoodAltar.hpp"
#include "NeutralAltar.hpp"
#include "Pew.hpp"

using boost::make_shared;

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
      altar = make_shared<EvilAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      altar = make_shared<NeutralAltar>(deity_id);
      break;
    case ALIGNMENT_RANGE_GOOD:
    default:
      altar = make_shared<GoodAltar>(deity_id);
      break;    
  }
  
  return altar;
}

// Generate a door based on the parameters provided.
FeaturePtr FeatureGenerator::generate_door()
{
  LockPtr lock_info;
  EntranceState door_state;
  FeaturePtr door = make_shared<Door>(lock_info, door_state);
  return door;
}

// Generate a fire pillar
FeaturePtr FeatureGenerator::generate_fire_pillar()
{
  FeaturePtr fire_pillar = make_shared<FirePillar>();
  return fire_pillar;
}

// Generate a happy, bubbly fountain
FeaturePtr FeatureGenerator::generate_fountain()
{
  FeaturePtr fountain = make_shared<Fountain>();
  return fountain;
}

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew(const PewDirection pew_direction)
{
  FeaturePtr pew;
  
  switch(pew_direction)
  {
    case PEW_DIRECTION_NORTH_SOUTH:
      pew = make_shared<Pew>();
      break;
    case PEW_DIRECTION_EAST_WEST:
    default:
      pew = make_shared<EastWestPew>();
      break;
  }

  return pew;
}

// Generate a wrought-iron bench
FeaturePtr FeatureGenerator::generate_bench()
{
  FeaturePtr bench = make_shared<Bench>();
  return bench;
}
