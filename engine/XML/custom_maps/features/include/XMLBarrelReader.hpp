#pragma once
#include "IXMLFeatureReader.hpp"

class XMLBarrelReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& barrel_node) const override;
};

