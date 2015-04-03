#include "XMLScriptsReader.hpp"
#include "ScriptConstants.hpp"

using namespace std;

map<string, string> XMLScriptsReader::get_scripts(const XMLNode& scripts_node)
{
  map<string, string> scripts;

  if (!scripts_node.is_null())
  {
    string special_day_script = XMLUtils::get_child_node_value(scripts_node, "SpecialDaysScript");
    scripts[ScriptConstants::SPECIAL_DAY_SCRIPT] = special_day_script;
  }

  return scripts;
}

// Read and return a ScriptDetails
ScriptDetails XMLScriptsReader::get_script_details(const XMLNode& script_details_node)
{
  ScriptDetails sd;

  if (!script_details_node.is_null())
  {
    string script = XMLUtils::get_child_node_value(script_details_node, "Script");
    int chance = XMLUtils::get_child_node_int_value(script_details_node, "Chance", 100);

    sd.set_script(script);
    sd.set_chance(chance);
  }

  return sd;
}
