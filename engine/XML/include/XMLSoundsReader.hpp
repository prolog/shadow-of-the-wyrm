#pragma once
#include <map>
#include <utility>
#include <unordered_map>
#include "Music.hpp"
#include "XMLReader.hpp"
#include "XMLDataStructures.hpp"

class XMLSoundsReader : public XMLReader
{
  public:
    std::map<std::pair<std::string, std::string>, std::string> get_effects(const XMLNode& xml_config_sounds_node);
    Music get_music(const XMLNode& xml_config_sounds_node);

  protected:
    void parse_effect(const XMLNode& eff_node, std::pair<std::pair<std::string, std::string>, std::string>& effect_id_and_location);
    void parse_song(const XMLNode& song_node, Song& song);
};

