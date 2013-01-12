#pragma once
#include "Map.hpp"
#include "XMLDataStructures.hpp"

// Used to parse features from the custom map XML, and place them on the 
// given map.
class XMLMapFeaturesReader
{
  public:
    void parse_features(const XMLNode& features_node, MapPtr map);
    void parse_feature_placement(const XMLNode& feature_placement_node, MapPtr map);    
};

class XMLMapFeatureReader
{
  public:
};

