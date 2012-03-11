#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "Door.hpp"

using boost::make_shared;

FeatureGenerator::FeatureGenerator()
{
}

FeatureGenerator::~FeatureGenerator()
{
}

// Generate a door based on the parameters provided.
FeaturePtr FeatureGenerator::generate_door()
{
  LockPtr lock_info;
  EntranceState door_state;
  FeaturePtr door = make_shared<Door>(lock_info, door_state);
  return door;
}
