#pragma once
#include "IXMLFeatureReader.hpp"

class XMLFenceReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& fence_node) const override;
};

