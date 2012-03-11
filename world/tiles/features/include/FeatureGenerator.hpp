#pragma once
#include "Feature.hpp"

class FeatureGenerator
{
  public:
    static FeaturePtr generate_door();

  protected:
    FeatureGenerator();
    ~FeatureGenerator();
};
