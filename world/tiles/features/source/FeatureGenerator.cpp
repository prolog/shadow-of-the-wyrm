#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "EvilAltar.hpp"
#include "Door.hpp"
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
      altar = FeaturePtr(new EvilAltar(deity_id));
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
      altar = FeaturePtr(new NeutralAltar(deity_id));
      break;
    case ALIGNMENT_RANGE_GOOD:
    default:
      altar = FeaturePtr(new GoodAltar(deity_id));
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

// Generate a pew
FeaturePtr FeatureGenerator::generate_pew()
{
  FeaturePtr pew = FeaturePtr(new Pew());
  return pew;
}
