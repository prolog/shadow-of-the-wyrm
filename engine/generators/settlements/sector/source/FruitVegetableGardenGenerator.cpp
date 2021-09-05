#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

FruitVegetableGardenGenerator::FruitVegetableGardenGenerator(const FruitVegetableGardenType new_fv_type, const string& new_deity_id, const AlignmentRange new_ar, const int new_col_spacing, const int new_row_spacing, const bool new_has_fence)
: GardenSectorFeature(new_deity_id, new_ar), vegetable_min(1), vegetable_max(1), fv_type(new_fv_type), col_spacing(new_col_spacing), row_spacing(new_row_spacing), has_fence(new_has_fence)
{
  populate_vegetable_map();
}

void FruitVegetableGardenGenerator::set_has_fence(const bool new_has_fence)
{
  has_fence = new_has_fence;
}

bool FruitVegetableGardenGenerator::get_has_fence() const
{
  return has_fence;
}

void FruitVegetableGardenGenerator::populate_vegetable_map()
{
  vegetable_map.clear();
  vegetable_map = std::map<int, std::string>{{1, ItemIdKeys::ITEM_ID_VEGETABLE_1},
                                             {2, ItemIdKeys::ITEM_ID_VEGETABLE_2},
                                             {3, ItemIdKeys::ITEM_ID_VEGETABLE_3},
                                             {4, ItemIdKeys::ITEM_ID_VEGETABLE_4},
                                             {5, ItemIdKeys::ITEM_ID_VEGETABLE_5},
                                             {6, ItemIdKeys::ITEM_ID_VEGETABLE_6}};
  
  vegetable_min = 1;
  vegetable_max = 6;
}

bool FruitVegetableGardenGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map == nullptr)
  {
    return false;
  }

  TileGenerator tg;

  int fv_start_row = start_coord.first;
  int fv_end_row = end_coord.first;
  int fv_start_col = start_coord.second;
  int fv_end_col = end_coord.second;
  int gate_row = 0;
  int gate_col = 0;

  vector<CardinalDirection> gate_dirs = { CardinalDirection::CARDINAL_DIRECTION_NORTH, CardinalDirection::CARDINAL_DIRECTION_SOUTH, CardinalDirection::CARDINAL_DIRECTION_EAST, CardinalDirection::CARDINAL_DIRECTION_WEST };
  Coordinate gate_coord;

  if (!gate_dirs.empty() && has_fence && (fv_end_row - fv_start_row > 2) && (fv_end_col - fv_start_col > 2))
  {
    CardinalDirection gate_dir = gate_dirs[RNG::range(0, gate_dirs.size() - 1)];
    gate_coord = SettlementGeneratorUtils::get_door_location(fv_start_row, fv_end_row, fv_start_col, fv_end_col, gate_dir);

    fv_start_row++;
    fv_start_col++;
    fv_end_row--;
    fv_end_col--;
  }

  vector<Coordinate> fencing = CoordUtils::get_perimeter_coordinates(start_coord, end_coord);

  for (const Coordinate& fc : fencing)
  {
    TilePtr tile = map->at(fc);

    if (tile != nullptr && !tile->has_feature())
    {
      FeaturePtr fence = FeatureGenerator::generate_fence();
      tile->set_feature(fence);
    }
  }

  if (has_fence)
  {
    FeaturePtr gate = FeatureGenerator::generate_gate();
    gate->set_material_type(MaterialType::MATERIAL_TYPE_WOOD);

    TilePtr gate_tile = map->at(gate_coord);

    if (gate_tile != nullptr)
    {
      gate_tile->set_feature(gate);
    }
  }

  for (int col = fv_start_col; col <= fv_end_col; col++)
  {
    int vegetable_idx = RNG::range(vegetable_min, vegetable_max);

    string vegetable_id = vegetable_map[vegetable_idx];

    // Spaces needed between vegetables to ensure that things grow.
    for (int row = fv_start_row; row <= fv_end_row; row++)
    {
      TilePtr field_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      
      if ((col % col_spacing == 0) && (row % row_spacing == 0))
      {
        // Generate a column of a particular vegetable.
        ItemPtr veg = ItemManager::create_item(vegetable_id);
        
        if (veg)
        {
          IInventoryPtr inv = field_tile->get_items();
          inv->add(veg);
        }          
      }
    
      map->insert(row, col, field_tile);      
    }
  }

  return true;
}

// Orchards
OrchardGenerator::OrchardGenerator()
: FruitVegetableGardenGenerator(FruitVegetableGardenType::FVG_TYPE_FRUIT)
{
}

bool OrchardGenerator::generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  TileGenerator tg;
  TileType tt = TileType::TILE_TYPE_UNDEFINED;

  for (int col = start_coord.second; col <= end_coord.second; col++)
  {
    TilePtr tile;

    if (col % col_spacing != 0)
    {
      continue;
    }

    // Spaces needed between vegetables to ensure that things grow.
    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      if (row % row_spacing == 0)
      {
        if (RNG::percent_chance(4))
        {
          tt = TileType::TILE_TYPE_MAGICAL_TREE;
        }
        else
        {
          tt = TileType::TILE_TYPE_FRUIT_TREE;
        }
      }
      else
      {
        tt = TileType::TILE_TYPE_UNDEFINED;
      }

      if (tt != TileType::TILE_TYPE_UNDEFINED)
      {
        tile = tg.generate(tt);
        map->insert(row, col, tile);
      }
    }
  }

  return true;
}
