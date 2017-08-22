#include "VoidGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "RNG.hpp"

using namespace std;

const string VoidGenerator::FEATURE_ID_COSMIC_DUST = "_cosmic_dust";
const string VoidGenerator::FEATURE_ID_DWARF_STAR = "_dwarf_star";
const string VoidGenerator::FEATURE_ID_RED_GIANT_STAR = "_red_giant_star";
const string VoidGenerator::FEATURE_ID_SUPERNOVA = "_supernova";
const string VoidGenerator::FEATURE_ID_BLACK_HOLE = "_black_hole";
const string VoidGenerator::FEATURE_ID_PULSAR = "_pulsar";

const int VoidGenerator::PCT_CHANCE_COSMIC_DUST = 40;
const int VoidGenerator::COSMIC_DUST_DIV_MIN = 4;
const int VoidGenerator::COSMIC_DUST_DIV_MAX = 20;

const int VoidGenerator::PCT_CHANCE_CELESTIAL_OBJECTS = 70;
const int VoidGenerator::PCT_CHANCE_SPIRAL_ARM = 50;

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
      Dimensions dim = result_map->size();
      int rows = dim.get_y();
      int cols = dim.get_x();

      int dust_div = RNG::range(COSMIC_DUST_DIV_MIN, COSMIC_DUST_DIV_MAX);
      TilesContainer& tiles = result_map->get_tiles();

      for (int i = 0; i < dust_div; i++)
      {
        int row = RNG::range(0, rows-1);
        int col = RNG::range(0, cols-1);

        TilePtr tile = result_map->at(row, col);
        
        if (tile != nullptr && !tile->has_feature())
        {
          FeaturePtr cosmic_dust = FeatureGenerator::generate_basic_feature(FEATURE_ID_COSMIC_DUST);
          tile->set_feature(cosmic_dust);
        }
      }
    }
  }
}

void VoidGenerator::add_celestial_objects(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_CELESTIAL_OBJECTS))
    {

    }
  }
}

void VoidGenerator::add_spiral_arm(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_SPIRAL_ARM))
    {

    }
  }
}
