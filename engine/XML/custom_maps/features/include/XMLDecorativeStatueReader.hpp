#pragma once
#include "IXMLFeatureReader.hpp"

class XMLDecorativeStatueReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& ds_node) const override;
};

