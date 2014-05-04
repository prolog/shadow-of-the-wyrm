#include "CoordUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreationUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "VaultPopulator.hpp"

using namespace std;

const int VaultPopulator::MIN_OUT_OF_DEPTH_INCR = 0;
const int VaultPopulator::MAX_OUT_OF_DEPTH_INCR = 10;

// Populate the vault with creatures and swag.
void VaultPopulator::populate_vault(MapPtr map, const TileType tile_type, const Coordinate& v_topleft, const Coordinate& v_bottomright)
{
  // Generate the "open tiles in the vault".
  set<Coordinate> vault_coords = CoordUtils::get_coordinates_in_range(make_pair(v_topleft.first + 1, v_topleft.second + 1), make_pair(v_bottomright.first - 1, v_bottomright.second - 1));

  populate_vault_creatures(map, tile_type, vault_coords);
  populate_vault_items(map, vault_coords);
}

void VaultPopulator::populate_vault_creatures(MapPtr map, const TileType tile_type, const set<Coordinate>& coords)
{
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();

  // Generate creatures and swag based on the danger levels.
  int danger_level = map->get_danger() + RNG::range(MIN_OUT_OF_DEPTH_INCR, MAX_OUT_OF_DEPTH_INCR);

  Rarity rarity = CreationUtils::generate_rarity();
  CreatureGenerationManager cgm;
  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(tile_type, danger_level, rarity);

  if (generation_map.size() > 0)
  {
    for (const Coordinate& c : coords)
    {
      TilePtr tile = map->at(c.first, c.second);
      CreaturePtr creature = cgm.generate_creature(am, generation_map);
      MapUtils::add_or_update_location(map, creature, c);
    }
  }
}

void VaultPopulator::populate_vault_items(MapPtr map, const set<Coordinate>& coords)
{
  // ...
}
