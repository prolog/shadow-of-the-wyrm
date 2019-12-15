#pragma once
#include <map>
#include "XMLReader.hpp"
#include "XMLDataStructures.hpp"

class XMLSpritesheetsReader : public XMLReader
{
  public:
    std::map<std::string, std::string> get_spritesheets(const XMLNode& xml_config_spritesheets_node);

  protected:
    void parse_spritesheet(const XMLNode& ss_node, std::map<std::string, std::string>& spritesheets);
};

