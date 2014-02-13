#pragma once
#include "IXMLFeatureReader.hpp"

class XMLPewReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& pew_node) const override;
};

