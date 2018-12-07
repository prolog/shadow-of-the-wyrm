#include "TombSectorFeature.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "DirectionUtils.hpp"
#include "EntranceTypes.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int TombSectorFeature::MIN_TOMB_HEIGHT = 5;
const int TombSectorFeature::MIN_TOMB_WIDTH = 5;

bool TombSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    int width = CoordUtils::get_width(start_coord, end_coord);
    int height = CoordUtils::get_height(start_coord, end_coord);

    if (width >= MIN_TOMB_WIDTH && height >= MIN_TOMB_HEIGHT)
    {
      GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_ROCK);
      GeneratorUtils::fill(map, make_pair(start_coord.first + 2, start_coord.second + 2), make_pair(end_coord.first - 2, end_coord.second - 2), TileType::TILE_TYPE_DUNGEON);
      generated = true;
    }

    vector<Direction> potential_door_locations = decorate_corners(map, start_coord, end_coord);
    generate_opening(map, start_coord, end_coord, potential_door_locations);
    generate_grave(map, start_coord, end_coord);
    generate_bones_and_treasure(map, start_coord, end_coord);
  }

  return generated;
}

vector<Direction> TombSectorFeature::decorate_corners(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  // first = N corners decorated
  // second = S corners decorated
  vector<Direction> door_locs;
  TileGenerator tg;

  if (map != nullptr)
  {
    vector<Coordinate> corners;
  
    // Potential chance to "round the corners".
    if (RNG::percent_chance(50))
    {
      corners.push_back(start_coord);
      corners.push_back(make_pair(start_coord.first, end_coord.second));
      door_locs.push_back(Direction::DIRECTION_NORTH);
    }

    if (RNG::percent_chance(50))
    {
      corners.push_back(make_pair(end_coord.first, start_coord.second));
      corners.push_back(end_coord);
      door_locs.push_back(Direction::DIRECTION_SOUTH);
    }

    for (const Coordinate& c : corners)
    {
      TilePtr tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(c, tile);
    }
  }

  if (door_locs.empty())
  {
    door_locs.push_back(Direction::DIRECTION_SOUTH);
  }

  return door_locs;
 }

void TombSectorFeature::generate_opening(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const vector<Direction>& door_locations)
{
  vector<Direction> potential_door_locations = door_locations;
  std::shuffle(potential_door_locations.begin(), potential_door_locations.end(), RNG::get_engine());

  if (!potential_door_locations.empty())
  {
    TileGenerator tg;
    Direction dir = potential_door_locations.at(0);
    CardinalDirection cd = DirectionUtils::to_cardinal_direction(dir);
    std::map<CardinalDirection, Coordinate> midway_points = CoordUtils::get_midway_coordinates(start_coord, end_coord);

    auto p_it = midway_points.find(cd);
    if (p_it != midway_points.end())
    {
      Coordinate c = p_it->second;
      Direction dig_dir = DirectionUtils::get_opposite_direction(dir);
      vector<Coordinate> dig_coords = { CoordUtils::get_new_coordinate(c, dig_dir, 1), CoordUtils::get_new_coordinate(c, dig_dir, 2) };
      TilePtr opening = tg.generate(TileType::TILE_TYPE_DUNGEON);
      DoorPtr door = FeatureGenerator::generate_door(EntranceStateType::ENTRANCE_TYPE_CLOSED);
      opening->set_feature(door);
      map->insert(c, opening);

      for (const Coordinate& d_c : dig_coords)
      {
        opening = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(d_c, opening);
      }
    }
  }
}

void TombSectorFeature::generate_grave(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    Coordinate centre_coord = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    TilePtr grave_tile = map->at(centre_coord);
    TileGenerator tg;

    if (grave_tile != nullptr)
    {
      // Generate a sarcophagus on the existing tile.
      if (RNG::x_in_y_chance(1, 3))
      {
        FeaturePtr sarcophagus = FeatureGenerator::generate_sarcophagus(MaterialType::MATERIAL_TYPE_MARBLE);
        grave_tile->set_feature(sarcophagus);
      }
      // Generate a new grave or barrow.
      else
      {
        TilePtr new_tile;

        if (RNG::x_in_y_chance(1, 3))
        {
          new_tile = tg.generate(TileType::TILE_TYPE_BARROW);
        }
        else
        {
          new_tile = tg.generate(TileType::TILE_TYPE_GRAVE);
        }

        if (new_tile != nullptr)
        {
          map->insert(centre_coord, new_tile);
        }
      }
    }
  }
}

void TombSectorFeature::generate_bones_and_treasure(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    vector<string> tomb_guardians = String::create_string_vector_from_csv_string(map->get_property(MapProperties::MAP_PROPERTIES_TOMB_GUARDIANS));
    CreatureFactory cf;
    Game& game = Game::instance();

    Coordinate centre = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    vector<Coordinate> adj_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), centre.first, centre.second);

    for (const Coordinate& c : adj_coords)
    {
      pair<string, uint> item_details = make_pair(ItemIdKeys::ITEM_ID_PILE_OF_BONES, 1);

      if (RNG::percent_chance(50))
      {
        item_details = make_pair(ItemIdKeys::ITEM_ID_CURRENCY, RNG::range(10, 30));
      }

      ItemPtr item = ItemManager::create_item(item_details.first, item_details.second);
      TilePtr tile = map->at(c);

      if (tile != nullptr && item != nullptr)
      {
        tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }

      // Potentially add a tomb guardian.
      if (!tomb_guardians.empty() && RNG::percent_chance(15))
      {
        string guardian_id = tomb_guardians.at(RNG::range(0, tomb_guardians.size()-1));
        CreaturePtr guardian = cf.create_by_creature_id(game.get_action_manager_ref(), guardian_id);

        if (guardian != nullptr)
        {
          GameUtils::add_new_creature_to_map(game, guardian, map, c);
        }
      }
    }
  }
}
