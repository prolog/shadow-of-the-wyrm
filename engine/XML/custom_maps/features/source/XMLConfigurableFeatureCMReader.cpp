#include "FeatureGenerator.hpp"
#include "XMLConfigurableFeatureCMReader.hpp"

using namespace std;

FeaturePtr XMLConfigurableFeatureCMReader::create(const XMLNode& cf_node) const
{
  FeaturePtr cf;

  if (!cf_node.is_null())
  {
    string id = XMLUtils::get_attribute_value(cf_node, "id");
    
    if (!id.empty())
    {
      cf = FeatureGenerator::generate_configurable_feature(id);
    }
  }

  return cf;
}
