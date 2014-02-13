#pragma once
#include "IXMLFeatureReader.hpp"

class XMLFountainReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& fountain_node) const override;
};

