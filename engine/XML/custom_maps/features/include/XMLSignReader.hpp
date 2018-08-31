#pragma once
#include "IXMLFeatureReader.hpp"

class XMLSignReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& pew_node) const override;
};

