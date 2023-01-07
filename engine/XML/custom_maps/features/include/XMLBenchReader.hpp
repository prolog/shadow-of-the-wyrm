#pragma once
#include "IXMLFeatureReader.hpp"

class XMLBenchReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& workbench_node) const override;
};

