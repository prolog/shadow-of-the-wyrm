#pragma once
#include "XMLReader.hpp"
#include "Feature.hpp"

class XMLBasicFeatureReader : public XMLReader
{
  public:
    FeatureMap get_basic_features(const XMLNode& basic_features_node);

  protected:
    // Returns a FeaturePtr.  Uses this approach instead of just being a void
    // function because the creation of the right feature type is dependent on
    // the values parsed.
    FeaturePtr get_basic_feature(const XMLNode& basic_feature_node);
};

