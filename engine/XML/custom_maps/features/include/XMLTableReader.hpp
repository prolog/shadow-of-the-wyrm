#pragma once
#include "IXMLFeatureReader.hpp"

class XMLTableReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& table_node) const override;
};

