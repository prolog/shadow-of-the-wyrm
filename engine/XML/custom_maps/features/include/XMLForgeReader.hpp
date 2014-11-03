#pragma once
#include "IXMLFeatureReader.hpp"

class XMLForgeReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& forge_node) const override;
};

