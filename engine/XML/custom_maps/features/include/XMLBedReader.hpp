#pragma once
#include "IXMLFeatureReader.hpp"

class XMLBedReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& bed_node) const override;
};

