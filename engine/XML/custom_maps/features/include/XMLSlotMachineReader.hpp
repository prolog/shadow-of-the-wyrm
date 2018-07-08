#pragma once
#include "IXMLFeatureReader.hpp"

class XMLSlotMachineReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& smachine_node) const override;
};

