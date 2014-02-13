#pragma once
#include "IXMLFeatureReader.hpp"

class XMLDoorReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& door_node) const override;
};

