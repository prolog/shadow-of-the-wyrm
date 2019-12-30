#include "XMLSpritesheetsReader.hpp"
#include "Log.hpp"

using namespace std;

// ID -> pair<filename, spritesheet references>
map<string, pair<string, unordered_map<string, Coordinate>>> XMLSpritesheetsReader::get_spritesheets(const XMLNode& xml_config_ss_node)
{
  map<string, pair<string, unordered_map<string, Coordinate>>> spritesheets;

  if (!xml_config_ss_node.is_null())
  {
    vector<XMLNode> ss_nodes = XMLUtils::get_elements_by_local_name(xml_config_ss_node, "Spritesheet");

    for (const auto& ss_node : ss_nodes)
    {
      parse_spritesheet(ss_node, spritesheets);
    }
  }

  return spritesheets;
}

void XMLSpritesheetsReader::parse_spritesheet(const XMLNode& ss_node, map<string, pair<string, unordered_map<string, Coordinate>>>& spritesheets)
{
  if (!ss_node.is_null())
  {
    string ss_id = XMLUtils::get_attribute_value(ss_node, "id");
    string ss_filename = XMLUtils::get_child_node_value(ss_node, "Location");
    unordered_map<string, Coordinate> refs;

    XMLNode references_node = XMLUtils::get_next_element_by_local_name(ss_node, "References");
    if (!references_node.is_null())
    {
      vector<XMLNode> reference_nodes = XMLUtils::get_elements_by_local_name(references_node, "Reference");

      for (auto& ref_node : reference_nodes)
      {
        string ref_id = XMLUtils::get_attribute_value(ref_node, "id");
        int row = XMLUtils::get_child_node_int_value(ref_node, "Row");
        int col = XMLUtils::get_child_node_int_value(ref_node, "Col");

        refs[ref_id] = {row, col};
      }
    }

    if (!ss_id.empty())
    {
      spritesheets[ss_id] = {ss_filename, refs};
    }
    else
    {
      Log::instance().error("Could not read spritesheet with empty ID - this ID is reserved for the text spritesheet configured in swyrm.ini.");
    }
  }
}
