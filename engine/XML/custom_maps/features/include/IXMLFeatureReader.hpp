#pragma once
#include "Feature.hpp"
#include "XMLDataStructures.hpp"

// Abstract factory to create a FeaturePtr from an XML node of the
// appropriate type.  The concrete class is instantiated by the
// XMLMapFeatureFactory.
class IXMLFeatureReader
{
  public:
    virtual ~IXMLFeatureReader() {};

    virtual FeaturePtr create(const XMLNode& node) const = 0;
};

typedef std::shared_ptr<IXMLFeatureReader> IXMLFeatureReaderPtr;