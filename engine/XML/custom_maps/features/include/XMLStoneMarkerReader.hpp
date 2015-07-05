#pragma once
#include "IXMLFeatureReader.hpp"

class XMLStoneMarkerReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& sm_node) const override;
};

