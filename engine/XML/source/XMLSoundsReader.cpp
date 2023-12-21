#include "XMLSoundsReader.hpp"

using namespace std;

map<string, string> XMLSoundsReader::get_effects(const XMLNode& xml_config_sounds_node)
{
  map<string, string> effects;

  if (!xml_config_sounds_node.is_null())
  {
    XMLNode effects_node = XMLUtils::get_next_element_by_local_name(xml_config_sounds_node, "Effects"); 
    
    if (!effects_node.is_null())
    {
      vector<XMLNode> effect_nodes = XMLUtils::get_elements_by_local_name(effects_node, "Effect");

      for (const auto& effect_node : effect_nodes)
      {
        pair<string, string> effect_details;
        parse_effect(effect_node, effect_details);

        effects[effect_details.first] = effect_details.second;
      }
    }
  }

  return effects;
}

void XMLSoundsReader::parse_effect(const XMLNode& effect_node, pair<string, string>& effect_details)
{
  if (!effect_node.is_null())
  {
    effect_details.first = XMLUtils::get_attribute_value(effect_node, "id");
    effect_details.second = XMLUtils::get_child_node_value(effect_node, "Location");
  }
}
