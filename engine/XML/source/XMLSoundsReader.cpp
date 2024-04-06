#include "XMLSoundsReader.hpp"
#include "Conversion.hpp"

using namespace std;

map<pair<string, string>, string> XMLSoundsReader::get_effects(const XMLNode& xml_config_sounds_node)
{
  map<pair<string, string>, string> effects;

  if (!xml_config_sounds_node.is_null())
  {
    XMLNode effects_node = XMLUtils::get_next_element_by_local_name(xml_config_sounds_node, "Effects"); 
    
    if (!effects_node.is_null())
    {
      vector<XMLNode> effect_nodes = XMLUtils::get_elements_by_local_name(effects_node, "Effect");

      for (const auto& effect_node : effect_nodes)
      {
        pair<pair<string, string>, string> effect_details;
        parse_effect(effect_node, effect_details);
        effects[effect_details.first] = effect_details.second;
      }
    }
  }

  return effects;
}

Music XMLSoundsReader::get_music(const XMLNode& xml_config_sounds_node)
{
  vector<Song> songs;

  if (!xml_config_sounds_node.is_null())
  {
    XMLNode music_node = XMLUtils::get_next_element_by_local_name(xml_config_sounds_node, "Music");

    if (!music_node.is_null())
    {
      vector<XMLNode> song_nodes = XMLUtils::get_elements_by_local_name(music_node, "Song");

      for (const auto& song_node : song_nodes)
      {
        Song song;
        parse_song(song_node, song);

        songs.push_back(song);
      }
    }
  }

  Music music(songs);
  return music;
}

void XMLSoundsReader::parse_effect(const XMLNode& effect_node, pair<pair<string, string>, string>& effect_details)
{
  if (!effect_node.is_null())
  {
    effect_details.first.first = XMLUtils::get_attribute_value(effect_node, "id");
    effect_details.first.second = XMLUtils::get_attribute_value(effect_node, "match");
    effect_details.second = XMLUtils::get_child_node_value(effect_node, "Location");
  }
}

void XMLSoundsReader::parse_song(const XMLNode& song_node, Song& song)
{
  if (!song_node.is_null())
  {
    string event = XMLUtils::get_attribute_value(song_node, "event");
    string id = XMLUtils::get_attribute_value(song_node, "id");
    string map_type_s = XMLUtils::get_attribute_value(song_node, "map_type");
    MapType map_type = MapType::MAP_TYPE_NULL;

    if (!map_type_s.empty())
    {
      map_type = static_cast<MapType>(String::to_int(map_type_s));
    }

    string tile_type_s = XMLUtils::get_attribute_value(song_node, "tile_type");
    TileType tile_type = TileType::TILE_TYPE_UNDEFINED;

    if (!tile_type_s.empty())
    {
      tile_type = static_cast<TileType>(String::to_int(tile_type_s));
    }

    string location = XMLUtils::get_child_node_value(song_node, "Location");

    song.set_event(event);
    song.set_id(id);
    song.set_tile_type(tile_type);
    song.set_map_type(map_type);
    song.set_location(location);
  }
}