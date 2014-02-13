#pragma once
#include "IXMLFeatureReader.hpp"

class XMLSarcophagusReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& sarcophagus_node) const override;
};

