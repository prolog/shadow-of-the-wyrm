#pragma once
#include "IXMLFeatureReader.hpp"

// Reads ConfigurableFeatures from custom maps
class XMLConfigurableFeatureCMReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& config_feature_node) const override;
};

