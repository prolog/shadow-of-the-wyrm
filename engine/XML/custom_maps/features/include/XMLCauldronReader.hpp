#pragma once
#include "IXMLFeatureReader.hpp"

class XMLCauldronReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& cauldron_node) const override;
};