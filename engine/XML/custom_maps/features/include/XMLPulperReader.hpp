#pragma once
#include "IXMLFeatureReader.hpp"

class XMLPulperReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& pulper_node) const override;
};

