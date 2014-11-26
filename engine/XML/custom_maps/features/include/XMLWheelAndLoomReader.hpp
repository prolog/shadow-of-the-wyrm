#pragma once
#include "IXMLFeatureReader.hpp"

class XMLWheelAndLoomReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& wheel_and_loom_node) const override;
};

