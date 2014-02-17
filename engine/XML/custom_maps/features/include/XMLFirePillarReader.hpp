#pragma once
#include "IXMLFeatureReader.hpp"

class XMLFirePillarReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& fire_pillar_node) const override;
};

