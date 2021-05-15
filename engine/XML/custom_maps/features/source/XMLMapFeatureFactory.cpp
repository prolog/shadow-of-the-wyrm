#include <string>
#include "AlignmentEnums.hpp"
#include "EntranceTypes.hpp"
#include "FeatureGenerator.hpp"
#include "IXMLFeatureReader.hpp"
#include "XMLAltarReader.hpp"
#include "XMLBedReader.hpp"
#include "XMLBarrelReader.hpp"
#include "XMLConfigurableFeatureCMReader.hpp"
#include "XMLDecorativeStatueReader.hpp"
#include "XMLDoorReader.hpp"
#include "XMLFirePillarReader.hpp"
#include "XMLForgeReader.hpp"
#include "XMLFountainReader.hpp"
#include "XMLJewelerWorkbenchReader.hpp"
#include "XMLKilnReader.hpp"
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
      feature_creator = std::make_unique<XMLAltarReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Barrel")).is_null())
    {
      feature_creator = std::make_unique<XMLBarrelReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Door")).is_null())
    {
      feature_creator = std::make_unique<XMLDoorReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "FirePillar")).is_null())
    {
      feature_creator = std::make_unique<XMLFirePillarReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Fountain")).is_null())
    {
      feature_creator = std::make_unique<XMLFountainReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pew")).is_null())
    {
      feature_creator = std::make_unique<XMLPewReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sarcophagus")).is_null())
    {
      feature_creator = std::make_unique<XMLSarcophagusReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Forge")).is_null())
    {
      feature_creator = std::make_unique<XMLForgeReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Tannery")).is_null())
    {
      feature_creator = std::make_unique<XMLTanneryReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "JewelerWorkbench")).is_null())
    {
      feature_creator = std::make_unique<XMLJewelerWorkbenchReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "WheelAndLoom")).is_null())
    {
      feature_creator = std::make_unique<XMLWheelAndLoomReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Bed")).is_null())
    {
      feature_creator = std::make_unique<XMLBedReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "StoneMarker")).is_null())
    {
      feature_creator = std::make_unique<XMLStoneMarkerReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Table")).is_null())
    {
      feature_creator = std::make_unique<XMLTableReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "SlotMachine")).is_null())
    {
      feature_creator = std::make_unique<XMLSlotMachineReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "ConfigurableFeature")).is_null())
    {
      feature_creator = std::make_unique<XMLConfigurableFeatureCMReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sign")).is_null())
    {
      feature_creator = std::make_unique<XMLSignReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "DecorativeStatue")).is_null())
    {
      feature_creator = std::make_unique<XMLDecorativeStatueReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pulper")).is_null())
    {
      feature_creator = std::make_unique<XMLPulperReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Kiln")).is_null())
    {
      feature_creator = std::make_unique<XMLKilnReader>();
    }

    assert(feature_creator != nullptr);
    feature = feature_creator->create(feature_node);
  }

  return feature;
}

