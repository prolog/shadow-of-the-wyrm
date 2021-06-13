#pragma once
#include "IXMLFeatureReader.hpp"

class XMLKilnReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& kiln_node) const override;
};

