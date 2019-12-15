#include "XMLSpritesheetsReader.hpp"
#include "Log.hpp"

using namespace std;

map<string, string> XMLSpritesheetsReader::get_spritesheets(const XMLNode& xml_config_ss_node)
{
  map<string, string> spritesheets;

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

void XMLSpritesheetsReader::parse_spritesheet(const XMLNode& ss_node, map<string, string>& spritesheets)
{
  if (!ss_node.is_null())
  {
    string ss_id = XMLUtils::get_attribute_value(ss_node, "id");
    string ss_filename = XMLUtils::get_node_value(ss_node);

    if (!ss_id.empty())
    {
      spritesheets[ss_id] = ss_filename;
    }
    else
    {
      Log::instance().error("Could not read spritesheet with empty ID - this ID is reserved for the text spritesheet configured in swyrm.ini.");
    }
  }
}
