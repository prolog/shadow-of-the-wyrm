#pragma once
#include "Feature.hpp"
#include "XMLDataStructures.hpp"

// Class for creating map features based on the feature present in the
// <choice> section of the FeaturePlacement.
class XMLMapFeatureFactory
{
  public:
    static FeaturePtr create_feature(const XMLNode& feature_placement_node);

  protected:
    XMLMapFeatureFactory();
    ~XMLMapFeatureFactory();
};

