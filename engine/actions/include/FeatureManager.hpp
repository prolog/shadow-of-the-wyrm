#pragma once
#include "Feature.hpp"

// A class to encapsulate handling blocking terrain features 
// (opening doors, pulling levers, etc) that have generic handling
// capabilities.
class FeatureManager
{
  public:
    FeatureManager();
    ~FeatureManager();
    
    bool handle(FeaturePtr feature);
};

