#pragma once
#include "IXMLFeatureReader.hpp"

// Reads BasicFeatures from Custom Maps (CM)
class XMLBasicFeatureCMReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& basic_feature_node) const override;
};

