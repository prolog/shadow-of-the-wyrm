#include "IXMLFeatureFactory.hpp"

// Create an Altar from the given Altar node.  See CustomMap.xsd for
// details.
class XMLAltarFactory : public IXMLFeatureFactory
{
  public:
    FeaturePtr create(const XMLNode& altar_node) const override;
};

