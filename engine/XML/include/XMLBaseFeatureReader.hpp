#pragma once
#include "XMLReader.hpp"
#include "Feature.hpp"

class XMLBaseFeatureReader : public XMLReader
{
  public:
    FeatureSymbolMap get_feature_symbols(const XMLNode& config_features_node, const bool force_ascii);

  protected:
    Symbol get_feature_symbol(const XMLNode& base_feature_node, const bool force_ascii);
};

