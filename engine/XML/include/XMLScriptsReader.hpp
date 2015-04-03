#pragma once
#include <map>
#include <string>
#include "XMLReader.hpp"
#include "ScriptDetails.hpp"

class XMLScriptsReader : public XMLReader
{
  public:
    std::map<std::string, std::string> get_scripts(const XMLNode& scripts_node);
    ScriptDetails get_script_details(const XMLNode& script_details_node);
};

