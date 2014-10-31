#include "XMLScriptsReader.hpp"
#include "ScriptConstants.hpp"

using namespace std;

map<string, string> XMLScriptsReader::get_scripts(const XMLNode& scripts_node)
{
  map<string, string> scripts;

  if (!scripts_node.is_null())
  {
    string special_day_script = XMLUtils::get_child_node_value(scripts_node, "SpecialDayScript");
    scripts[ScriptConstants::SPECIAL_DAY_SCRIPT] = special_day_script;
  }

  return scripts;
}

