#include <string>
#include "AlignmentEnums.hpp"
#include "Barrel.hpp"
#include "EntranceTypes.hpp"
#include "FeatureGenerator.hpp"
#include "IXMLFeatureReader.hpp"
#include "XMLAltarReader.hpp"
#include "XMLBarrelReader.hpp"
#include "XMLDoorReader.hpp"
#include "XMLFountainReader.hpp"
#include "XMLPewReader.hpp"
#include "XMLSarcophagusReader.hpp"
#include "XMLMapFeatureFactory.hpp"

using namespace std;

XMLMapFeatureFactory::XMLMapFeatureFactory()
{
}

XMLMapFeatureFactory::~XMLMapFeatureFactory()
{
}

FeaturePtr XMLMapFeatureFactory::create_feature(const XMLNode& feature_placement_node)
{
  FeaturePtr feature;

  if (!feature_placement_node.is_null())
  {
    IXMLFeatureReaderPtr feature_creator;

    XMLNode feature_node;

    if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Altar")).is_null())
    {
      feature_creator = std::make_shared<XMLAltarReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Barrel")).is_null())
    {
      feature_creator = std::make_shared<XMLBarrelReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Door")).is_null())
    {
      feature_creator = std::make_shared<XMLDoorReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Fountain")).is_null())
    {
      feature_creator = std::make_shared<XMLFountainReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pew")).is_null())
    {
      feature_creator = std::make_shared<XMLPewReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sarcophagus")).is_null())
    {
      feature_creator = std::make_shared<XMLSarcophagusReader>();
    }

    assert(feature_creator != nullptr);
    feature = feature_creator->create(feature_node);
  }

  return feature;
}

