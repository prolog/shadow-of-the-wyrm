#include "IXMLFeatureReader.hpp"

// Create an Altar from the given Altar node.  See CustomMap.xsd for
// details.
class XMLAltarReader : public IXMLFeatureReader
{
  public:
    FeaturePtr create(const XMLNode& altar_node) const override;
};

