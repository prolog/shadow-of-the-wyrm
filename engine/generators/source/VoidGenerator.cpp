#include "VoidGenerator.hpp"
#include "BresenhamLine.hpp"
#include "FeatureGenerator.hpp"
#include "RNG.hpp"

using namespace std;

const string VoidGenerator::FEATURE_ID_COSMIC_DUST = "_cosmic_dust";
const string VoidGenerator::FEATURE_ID_DWARF_STAR = "_dwarf_star";
const string VoidGenerator::FEATURE_ID_RED_GIANT_STAR = "_red_giant_star";
const string VoidGenerator::FEATURE_ID_SUPERNOVA = "_supernova";
const string VoidGenerator::FEATURE_ID_BLACK_HOLE = "_black_hole";
const string VoidGenerator::FEATURE_ID_PULSAR = "_pulsar";
const string VoidGenerator::FEATURE_ID_SPIRAL_ARM = "_spiral_arm";

const int VoidGenerator::PCT_CHANCE_COSMIC_DUST = 40;
const int VoidGenerator::COSMIC_DUST_DIV_MIN = 4;
const int VoidGenerator::COSMIC_DUST_DIV_MAX = 20;
const int VoidGenerator::CELESTIAL_OBJECTS_DIV_MIN = 10;
const int VoidGenerator::CELESTIAL_OBJECTS_DIV_MAX = 20;

const int VoidGenerator::PCT_CHANCE_CELESTIAL_OBJECTS = 70;

const int VoidGenerator::PCT_CHANCE_SPIRAL_ARM = 50;
const int VoidGenerator::SPIRAL_ARM_DENSITY_PCT_MIN = 40;
const int VoidGenerator::SPIRAL_ARM_DENSITY_PCT_MAX = 100;

VoidGenerator::VoidGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_VOID)
{
}

MapPtr VoidGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_VOID);

  add_cosmic_dust(result_map);
  add_celestial_objects(result_map);
  add_spiral_arm(result_map);

  return result_map;
}

void VoidGenerator::add_cosmic_dust(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_COSMIC_DUST))
    {
      vector<string> feature_ids = {FEATURE_ID_COSMIC_DUST};
      int dust_div = RNG::range(COSMIC_DUST_DIV_MIN, COSMIC_DUST_DIV_MAX);

      add_random_features(result_map, feature_ids, dust_div);
    }
  }
}

void VoidGenerator::add_celestial_objects(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_CELESTIAL_OBJECTS))
    {
      vector<string> celestial_ids = {FEATURE_ID_BLACK_HOLE, 
                                      FEATURE_ID_DWARF_STAR, 
                                      FEATURE_ID_RED_GIANT_STAR, 
                                      FEATURE_ID_SUPERNOVA, 
                                      FEATURE_ID_PULSAR};

      int celestial_objects_div = RNG::range(CELESTIAL_OBJECTS_DIV_MIN, CELESTIAL_OBJECTS_DIV_MAX);
      add_random_features(result_map, celestial_ids, celestial_objects_div);
    }
  }
}

void VoidGenerator::add_spiral_arm(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_SPIRAL_ARM))
    {
      vector<vector<Coordinate>> arm_coords;
      int arm_size = RNG::range(3, 6);
      int density_pct = RNG::range(SPIRAL_ARM_DENSITY_PCT_MIN, SPIRAL_ARM_DENSITY_PCT_MAX);
      BresenhamLine bl;

      Dimensions dim = result_map->size();
      int rows = dim.get_y();
      int cols = dim.get_x();
      int x1 = 0;
      int x2 = 0;
      int y1 = 0;
      int y2 = 0;

      bool horizontal = RNG::percent_chance(50);
      
      if (horizontal)
      {
        x2 = cols - 1;
        y1 = RNG::range(0, rows-1);
        y2 = RNG::range(0, rows-1);

        if (y1 == y2)
        {
          y2 == 0 ? y2 = rows / 2 : y2 /= 2;
        }

        for (int i = 0; i < arm_size; i++)
        {
          vector<Coordinate> coords = bl.get_points_in_line(y1+i, x1, y2, x2);
          arm_coords.push_back(coords);
        }
      }
      else
      {
        y2 = rows-1;
        x1 = RNG::range(0, cols-1);
        x2 = RNG::range(0, cols-1);

        if (x1 == x2)
        {
          x2 == 0 ? x2 = cols / 2 : x2 /= 2;
        }

        for (int i = 0; i < arm_size; i++)
        {
          vector<Coordinate> coords = bl.get_points_in_line(y1, x1+i, y2, x2);
          arm_coords.push_back(coords);
        }
      }

      for (vector<Coordinate>& vc : arm_coords)
      {
        for (const Coordinate& c : vc)
        {
          if (RNG::percent_chance(density_pct))
          {
            TilePtr tile = result_map->at(c);

            if (tile && !tile->has_feature())
            {
              FeaturePtr sp_arm = FeatureGenerator::generate_basic_feature(FEATURE_ID_SPIRAL_ARM);

              if (sp_arm != nullptr)
              {
                tile->set_feature(sp_arm);
              }
            }
          }
        }
      }
    }
  }
}

void VoidGenerator::add_random_features(MapPtr result_map, const vector<string>& feature_ids, const int num_features)
{
  if (result_map != nullptr && !feature_ids.empty())
  {
    Dimensions dim = result_map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();

    TilesContainer& tiles = result_map->get_tiles();

    for (int i = 0; i < num_features; i++)
    {
      int row = RNG::range(0, rows - 1);
      int col = RNG::range(0, cols - 1);

      TilePtr tile = result_map->at(row, col);

      if (tile != nullptr && !tile->has_feature())
      {
        string feature_id = feature_ids.at(RNG::range(0, feature_ids.size() - 1));
        FeaturePtr feat = FeatureGenerator::generate_basic_feature(feature_id);

        if (feat != nullptr)
        {
          tile->set_feature(feat);
        }
      }
    }
  }
}
