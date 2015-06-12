#include "TreasureRoomPopulator.hpp"
#include "CoordUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemGenerationManager.hpp"
#include "RNG.hpp"

using namespace std;

// Populate a treasure room:
// - Fire pillars in the room corners
// - 2-4 creatures between the danger level and 5 levels higher
// - Item with additional base enchants in the centre
void TreasureRoomPopulator::populate_treasure_room(MapPtr current_map, const TileType tile_type, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall)
{
  if (current_map)
  {
    generate_corner_features(current_map, start_row, end_row_wall, start_col, end_col_wall);
    generate_creatures(current_map, tile_type, danger_level, start_row, end_row_wall, start_col, end_col_wall);
    generate_treasure(current_map, danger_level, start_row, end_row_wall, start_col, end_col_wall);
  }
}

// Generate pillars or fountains at the edge of the room.
void TreasureRoomPopulator::generate_corner_features(MapPtr current_map, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall)
{
  FeaturePtr feat;
  
  if (RNG::percent_chance(33))
  {
     feat = FeatureGenerator::generate_fire_pillar();
  }
  else if (RNG::percent_chance(33))
  {
    feat = FeatureGenerator::generate_fountain();
  }
  else
  {
    feat = FeatureGenerator::generate_sarcophagus(MaterialType::MATERIAL_TYPE_STEEL);
  }

  TilePtr feat_tile = current_map->at(start_row, start_col);
  feat_tile->set_feature(feat);
  
  feat = FeaturePtr(feat->clone());
  feat_tile = current_map->at(start_row, end_col_wall - 1);
  feat_tile->set_feature(feat);

  feat = FeaturePtr(feat->clone());
  feat_tile = current_map->at(end_row_wall - 1, start_col);
  feat_tile->set_feature(feat);

  feat = FeaturePtr(feat->clone());
  feat_tile = current_map->at(end_row_wall - 1, end_col_wall - 1);
  feat_tile->set_feature(feat);
}

// Generate the creatures in the treasure room.
void TreasureRoomPopulator::generate_creatures(MapPtr current_map, const TileType tile_type, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall)
{
  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();

  vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(make_pair(start_row, start_col), make_pair(end_row_wall - 1, end_col_wall - 1));
  CreatureGenerationManager cgm;

  map<string, string> map_properties = current_map->get_properties();
  CreatureGenerationMap generation_map = cgm.generate_creature_generation_map(tile_type, current_map->get_permanent(), danger_level, danger_level + 5, Rarity::RARITY_RARE, map_properties);

  // Generate a few creatures, and place them in random positions throughout the room.
  int num_creatures = RNG::range(2, 4);
  shuffle(coords.begin(), coords.end(), RNG::get_engine());

  for (int i = 0; i < num_creatures; i++)
  {
    if (coords.empty())
    {
      break;
    }
    else
    {
      Coordinate c = coords.back();
      coords.pop_back();

      TilePtr tile = current_map->at(c.first, c.second);
      CreaturePtr creature = cgm.generate_creature(am, generation_map);
      GameUtils::add_new_creature_to_map(game, creature, current_map, c);
    }
  }
}

// Generate the treasure in the centre of the room.
void TreasureRoomPopulator::generate_treasure(MapPtr current_map, const int danger_level, const int start_row, const int end_row_wall, const int start_col, const int end_col_wall)
{
  if (current_map)
  {
    int centre_row = (start_row + (end_row_wall - 1)) / 2;
    int centre_col = (start_col + (end_col_wall - 1)) / 2;

    TilePtr tile = current_map->at(centre_row, centre_col);

    if (tile)
    {
      Game& game = Game::instance();
      ActionManager& am = game.get_action_manager_ref();

      // Generate an item.
      ItemGenerationManager igm;
      ItemGenerationVec generation_vec = igm.generate_item_generation_vec(danger_level / 2, RNG::range(danger_level, danger_level + 5), Rarity::RARITY_RARE);

      ItemPtr generated_item = igm.generate_item(am, generation_vec, RNG::range(2, 4));

      if (generated_item)
      {
        // Add a number of extra enchants, and then add the item to the tile.
        generated_item->enchant(RNG::range(2, 3));
        tile->get_items()->add(generated_item);
      }
    }
  }
}