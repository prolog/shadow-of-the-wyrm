#pragma once
#include <map>
#include <string>
#include "XMLReader.hpp"

class XMLScriptsReader : public XMLReader
{
  public:
    std::map<std::string, std::string> get_scripts(const XMLNode& scripts_node);
};

