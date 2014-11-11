#pragma once
#include "IXMLFeatureReader.hpp"

class XMLTanneryReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& tannery_node) const override;
};

