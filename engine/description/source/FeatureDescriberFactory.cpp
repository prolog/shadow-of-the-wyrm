#include "FeatureDescriberFactory.hpp"
#include "FeatureDescriber.hpp"
#include "BlindFeatureDescriber.hpp"

FeatureDescriberFactory::FeatureDescriberFactory()
{
}

FeatureDescriberPtr FeatureDescriberFactory::create_feature_describer(const bool player_blind, FeaturePtr feature)
{
  FeatureDescriberPtr describer;

  if (player_blind)
  {
    describer = std::make_shared<BlindFeatureDescriber>();
  }
  else
  {
    describer = std::make_shared<FeatureDescriber>(feature);
  }

  return describer;
}

