#pragma once
#include "IXMLFeatureReader.hpp"

class XMLJewelerWorkbenchReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& workbench_node) const override;
};

