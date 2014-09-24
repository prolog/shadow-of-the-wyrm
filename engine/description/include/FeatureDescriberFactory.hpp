#pragma once
#include "FeatureDescriber.hpp"
#include "Feature.hpp"

// Create a FeatureDescriberPtr based on whether the player is blind or
// not.
class FeatureDescriberFactory
{
  public:
    static FeatureDescriberPtr create_feature_describer(const bool player_blind, const FeaturePtr feature);

  protected:
    FeatureDescriberFactory();
};

