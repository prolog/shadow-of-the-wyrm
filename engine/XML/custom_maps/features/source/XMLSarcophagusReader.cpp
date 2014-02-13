#include "FeatureGenerator.hpp"
#include "XMLSarcophagusReader.hpp"

using namespace std;

// Read in a Sarcophagus (in the form of a FeaturePtr) from the given
// Sarcophagus XML node - see CustomMap.xsd for details.
FeaturePtr XMLSarcophagusReader::create(const XMLNode& sarcophagus_node) const
{
  MaterialType material_type = MATERIAL_TYPE_STONE;
  XMLNode material_node = XMLUtils::get_next_element_by_local_name(sarcophagus_node, "Material");
  if (!material_node.is_null())
  {
    material_type = static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node));
  }

  SarcophagusPtr sarcophagus = FeatureGenerator::generate_sarcophagus(material_type);

  string inscription_sid = XMLUtils::get_child_node_value(sarcophagus_node, "Inscription");
  sarcophagus->set_inscription_sid(inscription_sid);

  return sarcophagus;
}

