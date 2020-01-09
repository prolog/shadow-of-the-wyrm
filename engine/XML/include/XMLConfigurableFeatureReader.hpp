#pragma once
#include "XMLReader.hpp"
#include "Feature.hpp"

class XMLConfigurableFeatureReader : public XMLReader
{
  public:
    FeatureMap get_configurable_features(const XMLNode& config_features_node, const bool force_ascii);

  protected:
    // Returns a FeaturePtr.  Uses this approach instead of just being a void
    // function because the creation of the right feature type is dependent on
    // the values parsed.
    FeaturePtr get_configurable_feature(const XMLNode& config_feature_node, const bool force_ascii);
};

