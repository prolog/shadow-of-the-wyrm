#pragma once
#include "Feature.hpp"
#include "XMLDataStructures.hpp"

// Abstract factory to create a FeaturePtr from an XML node of the
// appropriate type.  The concrete class is instantiated by the
// XMLMapFeatureFactory.
class IXMLFeatureFactory
{
  public:
    virtual ~IXMLFeatureFactory() {};

    virtual FeaturePtr create(const XMLNode& node) const = 0;
};

typedef std::shared_ptr<IXMLFeatureFactory> IXMLFeatureFactoryPtr;