#pragma once
#include "IXMLFeatureReader.hpp"

class XMLHiveReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& hive_node) const override;
};