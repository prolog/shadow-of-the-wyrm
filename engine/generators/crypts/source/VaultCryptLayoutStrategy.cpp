#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "CoordUtils.hpp"
#include "Conversion.hpp"
#include "FeatureGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "Tool.hpp"
#include "VaultCryptLayoutStrategy.hpp"
#include "VaultPopulator.hpp"

using namespace std;

// Create a central vault with creatures.
void VaultCryptLayoutStrategy::create_layout(MapPtr map, const tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  pair<Coordinate, Coordinate> vault_coords = generate_vault(map, stair_loc_and_room_boundary);

  // Fill the vault with creatures and items.
  VaultPopulator vp;
  vp.populate_vault(map, TileType::TILE_TYPE_CRYPT, vault_coords.first, vault_coords.second);
}

// Create the central vault.
pair<Coordinate, Coordinate> VaultCryptLayoutStrategy::generate_vault(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  Coordinate top_left = std::get<1>(stair_loc_and_room_boundary);
  Coordinate bottom_right = std::get<2>(stair_loc_and_room_boundary);

  int mid_height = (top_left.first + bottom_right.first) / 2;
  int mid_width = (top_left.second + bottom_right.second) / 2;

  // Determine the vault's height and width.
  int vh_min = 5, vw_min = 5;
  int vh_max = 7, vw_max = 7;

  int vh = RNG::range(vh_min, vh_max);
  int vw = RNG::range(vw_min, vw_max);

  Coordinate v_topleft(mid_height - (vh / 2), mid_width - (vw / 2));
  Coordinate v_bottomright(mid_height + (vh / 2), mid_width + (vw / 2));

  vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(v_topleft, v_bottomright);

  // Create the vault.
  TileGenerator tg;
  for (const Coordinate& c : coords)
  {
    TilePtr tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(c.first, c.second, tile);
  }

  generate_vault_entrance(map, mid_height, mid_width, vh, vw, std::get<0>(stair_loc_and_room_boundary));
  return make_pair(v_topleft, v_bottomright);
}

void VaultCryptLayoutStrategy::generate_vault_entrance(MapPtr map, const int mid_height, const int mid_width, const int vh, const int vw, const Coordinate& stair_coord)
{
  // Create the door.
  Direction d = static_cast<Direction>(RNG::range(static_cast<int>(Direction::DIRECTION_NORTH), static_cast<int>(Direction::DIRECTION_WEST)));
  Coordinate door_coords = get_door_location(d, mid_height, mid_width, vh, vw);

  // Change the associated tile to TileType::TILE_TYPE_DUNGEON, and add a door.
  TileGenerator tg;

  boost::uuids::uuid id = boost::uuids::random_generator()();
  std::string lock_id = Uuid::to_string(id);
  TilePtr door_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
  DoorPtr door = FeatureGenerator::generate_door();
  LockPtr lock = std::make_shared<Lock>(lock_id, true);
  door->set_lock(lock);
  EntranceStateType entrance_state = EntranceStateType::ENTRANCE_TYPE_CLOSED;
  door->get_state_ref().set_state(entrance_state);

  door_tile->set_feature(door);

  map->insert(door_coords.first, door_coords.second, door_tile);

  // Create the key, placing it on the up staircase.
  ToolPtr door_key = dynamic_pointer_cast<Tool>(ItemManager::create_item("_crypt_key"));

  if (door_key != nullptr)
  {
    door_key->set_lock_id(lock_id);

    TilePtr stair_tile = map->at(stair_coord);
    stair_tile->get_items()->add(door_key);
  }
}

// Given the vault location details and the cardinal direction of the vault
// entrance, get the coordinates.
Coordinate VaultCryptLayoutStrategy::get_door_location(const Direction d, const int mid_height, const int mid_width, const int vh, const int vw)
{
  int d_y, d_x;

  switch (d)
  {
    case Direction::DIRECTION_NORTH:
      d_y = mid_height - (vh / 2);
      d_x = mid_width;
      break;
    case Direction::DIRECTION_SOUTH:
      d_y = mid_height + (vh / 2);
      d_x = mid_width;
      break;
    case Direction::DIRECTION_EAST:
      d_y = mid_height;
      d_x = mid_width + (vw / 2);
      break;
    case Direction::DIRECTION_WEST:
    default:
      d_y = mid_height;
      d_x = mid_width - (vw / 2);
      break;
  }

  return make_pair(d_y, d_x);
}

