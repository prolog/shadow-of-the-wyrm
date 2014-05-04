#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreationUtils.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "Tool.hpp"
#include "VaultCryptLayoutStrategy.hpp"

using namespace std;

const int VaultCryptLayoutStrategy::MIN_OUT_OF_DEPTH_INCR = 0;
const int VaultCryptLayoutStrategy::MAX_OUT_OF_DEPTH_INCR = 10;

// Create a central vault with creatures.
void VaultCryptLayoutStrategy::create_layout(MapPtr map, const tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  pair<Coordinate, Coordinate> vault_coords = generate_vault(map, stair_loc_and_room_boundary);

  // Fill the vault with creatures and items.
  populate_vault(map, vault_coords.first, vault_coords.second);
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

  set<Coordinate> coords = CoordUtils::get_perimeter_coordinates(v_topleft, v_bottomright);

  // Create the vault.
  TileGenerator tg;
  for (const Coordinate& c : coords)
  {
    TilePtr tile = tg.generate(TILE_TYPE_ROCK);
    map->insert(c.first, c.second, tile);
  }

  generate_vault_entrance(map, mid_height, mid_width, vh, vw, std::get<0>(stair_loc_and_room_boundary));
  return make_pair(v_topleft, v_bottomright);
}

void VaultCryptLayoutStrategy::generate_vault_entrance(MapPtr map, const int mid_height, const int mid_width, const int vh, const int vw, const Coordinate& stair_coord)
{
  // Create the door.

  Direction d = static_cast<Direction>(RNG::range(DIRECTION_NORTH, DIRECTION_WEST));
  Coordinate door_coords = get_door_location(d, mid_height, mid_width, vh, vw);

  // Change the associated tile to TILE_TYPE_DUNGEON, and add a door.
  TileGenerator tg;

  boost::uuids::uuid id = boost::uuids::random_generator()();
  std::string lock_id = Uuid::to_string(id);
  TilePtr door_tile = tg.generate(TILE_TYPE_DUNGEON);
  DoorPtr door = FeatureGenerator::generate_door();
  LockPtr lock = std::make_shared<Lock>(lock_id, true);
  door->set_lock(lock);
  EntranceStateType entrance_state = ENTRANCE_TYPE_CLOSED;
  door->get_state_ref().set_state(entrance_state);

  door_tile->set_feature(door);

  map->insert(door_coords.first, door_coords.second, door_tile);

  // Create the key, placing it on the up staircase.
  ToolPtr door_key = dynamic_pointer_cast<Tool>(ItemManager::create_item("_crypt_key"));

  if (door_key != nullptr)
  {
    door_key->set_lock_id(lock_id);

    TilePtr stair_tile = map->at(stair_coord);
    stair_tile->get_items().add(door_key);
  }
}

// Given the vault location details and the cardinal direction of the vault
// entrance, get the coordinates.
Coordinate VaultCryptLayoutStrategy::get_door_location(const Direction d, const int mid_height, const int mid_width, const int vh, const int vw)
{
  int d_y, d_x;

  switch (d)
  {
    case DIRECTION_NORTH:
      d_y = mid_height - (vh / 2);
      d_x = mid_width;
      break;
    case DIRECTION_SOUTH:
      d_y = mid_height + (vh / 2);
      d_x = mid_width;
      break;
    case DIRECTION_EAST:
      d_y = mid_height;
      d_x = mid_width + (vw / 2);
      break;
    case DIRECTION_WEST:
    default:
      d_y = mid_height;
      d_x = mid_width - (vw / 2);
      break;
  }

  return make_pair(d_y, d_x);
}

// Populate the vault with creatures and swag.
void VaultCryptLayoutStrategy::populate_vault(MapPtr map, const Coordinate& v_topleft, const Coordinate& v_bottomright)
{
  populate_vault_creatures(map, v_topleft, v_bottomright);
  populate_vault_items(map, v_topleft, v_bottomright);
}

void VaultCryptLayoutStrategy::populate_vault_creatures(MapPtr map, const Coordinate& v_topleft, const Coordinate& v_bottomright)
{
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();

  // Generate creatures and swag based on the danger levels.
  int danger_level = map->get_danger() + RNG::range(MIN_OUT_OF_DEPTH_INCR, MAX_OUT_OF_DEPTH_INCR);

  int vi_startrow = v_topleft.first + 1;
  int vi_endrow = v_bottomright.first - 1;
  int vi_startcol = v_topleft.second + 1;
  int vi_endcol = v_bottomright.second - 1;

  Rarity rarity = CreationUtils::generate_rarity();
  CreatureGenerationManager cgm;
  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(TILE_TYPE_CRYPT, danger_level, rarity);

  if (generation_map.size() > 0)
  {
    for (int row = vi_startrow; row <= vi_endrow; row++)
    {
      for (int col = vi_startcol; col <= vi_endcol; col++)
      {
        TilePtr tile = map->at(row, col);
        CreaturePtr creature = cgm.generate_creature(am, generation_map);
        MapUtils::add_or_update_location(map, creature, make_pair(row, col));
      }
    }
  }
}

void VaultCryptLayoutStrategy::populate_vault_items(MapPtr map, const Coordinate& v_topleft, const Coordinate& v_bottomright)
{
  // ...
}