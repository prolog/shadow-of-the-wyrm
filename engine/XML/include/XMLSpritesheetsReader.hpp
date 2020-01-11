#pragma once
#include <map>
#include <unordered_map>
#include "XMLReader.hpp"
#include "XMLDataStructures.hpp"

class XMLSpritesheetsReader : public XMLReader
{
  public:
    std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>> get_spritesheets(const XMLNode& xml_config_spritesheets_node);

  protected:
    void parse_spritesheet(const XMLNode& ss_node, std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>>& spritesheets);
};

