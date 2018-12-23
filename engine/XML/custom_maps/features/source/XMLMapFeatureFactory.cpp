#include <string>
#include "AlignmentEnums.hpp"
#include "EntranceTypes.hpp"
#include "FeatureGenerator.hpp"
#include "IXMLFeatureReader.hpp"
#include "XMLAltarReader.hpp"
#include "XMLBedReader.hpp"
#include "XMLBarrelReader.hpp"
#include "XMLBasicFeatureCMReader.hpp"
#include "XMLDecorativeStatueReader.hpp"
#include "XMLDoorReader.hpp"
#include "XMLFirePillarReader.hpp"
#include "XMLForgeReader.hpp"
#include "XMLFountainReader.hpp"
#include "XMLJewelerWorkbenchReader.hpp"
#include "XMLPewReader.hpp"
#include "XMLPulperReader.hpp"
#include "XMLSarcophagusReader.hpp"
#include "XMLSignReader.hpp"
#include "XMLSlotMachineReader.hpp"
#include "XMLStoneMarkerReader.hpp"
#include "XMLTableReader.hpp"
#include "XMLTanneryReader.hpp"
#include "XMLMapFeatureFactory.hpp"
#include "XMLWheelAndLoomReader.hpp"

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
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "FirePillar")).is_null())
    {
      feature_creator = std::make_shared<XMLFirePillarReader>();
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
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Forge")).is_null())
    {
      feature_creator = std::make_shared<XMLForgeReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Tannery")).is_null())
    {
      feature_creator = std::make_shared<XMLTanneryReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "JewelerWorkbench")).is_null())
    {
      feature_creator = std::make_shared<XMLJewelerWorkbenchReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "WheelAndLoom")).is_null())
    {
      feature_creator = std::make_shared<XMLWheelAndLoomReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Bed")).is_null())
    {
      feature_creator = std::make_shared<XMLBedReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "StoneMarker")).is_null())
    {
      feature_creator = std::make_shared<XMLStoneMarkerReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Table")).is_null())
    {
      feature_creator = std::make_shared<XMLTableReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "SlotMachine")).is_null())
    {
      feature_creator = std::make_shared<XMLSlotMachineReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "BasicFeature")).is_null())
    {
      feature_creator = std::make_shared<XMLBasicFeatureCMReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sign")).is_null())
    {
      feature_creator = std::make_shared<XMLSignReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "DecorativeStatue")).is_null())
    {
      feature_creator = std::make_shared<XMLDecorativeStatueReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pulper")).is_null())
    {
      feature_creator = std::make_shared<XMLPulperReader>();
    }

    assert(feature_creator != nullptr);
    feature = feature_creator->create(feature_node);
  }

  return feature;
}

