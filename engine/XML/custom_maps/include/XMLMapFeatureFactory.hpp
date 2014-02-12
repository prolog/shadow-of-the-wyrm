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

    static FeaturePtr create_altar(const XMLNode& altar_node);
    static FeaturePtr create_barrel(const XMLNode& barrel_node);
    static FeaturePtr create_door(const XMLNode& door_node);
    static FeaturePtr create_fountain(const XMLNode& fountain_node);
    static FeaturePtr create_pew(const XMLNode& pew_node);
    static FeaturePtr create_sarcophagus(const XMLNode& sarcophagus_node);
};

