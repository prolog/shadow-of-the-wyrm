#include "ShrineGenerator.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "MapProperties.hpp"

using namespace std;

ShrineGenerator::ShrineGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_SHRINE), base_map(new_base_map)
{
}

// Shrines have a list of creatures, and a list of preset locations.  Each
// preset should have a creature.  Right now, for shrines, these preset
// locations are all the floor (dungeon) tiles, so go through the tiles
// in the map and add the appopriate ones.
void ShrineGenerator::add_dungeon_tiles_to_preset_locations(MapPtr map)
{
  vector<Coordinate> preset_locs;

  if (map != nullptr)
  {
    TilesContainer tc = map->get_tiles();

    for (const auto& tile_pair : tc)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
      {
        string key = tile_pair.first;
        Coordinate c = MapUtils::convert_map_key_to_coordinate(key);
        preset_locs.push_back(c);
      }
    }

    map->set_preset_locations(preset_locs);
  }
}

// Place the shrine's relic at the specified location.
void ShrineGenerator::place_relic(MapPtr map, const int mid_row, const int mid_col)
{
  if (map != nullptr)
  {
    string relic_id = get_additional_property(MapProperties::MAP_PROPERTIES_RELIC_ID);

    if (!relic_id.empty())
    {
      ItemManager im;

      ItemPtr relic = im.create_item(relic_id);
      TilePtr relic_tile = map->at(mid_row, mid_col);

      if (relic_tile != nullptr)
      {
        relic_tile->get_items()->add_front(relic);
      }
    }
  }
}