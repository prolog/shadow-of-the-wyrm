#include "VoidGenerator.hpp"

using namespace std;

const string VoidGenerator::FEATURE_ID_COSMIC_DUST = "_cosmic_dust";
const string VoidGenerator::FEATURE_ID_DWARF_STAR = "_dwarf_star";
const string VoidGenerator::FEATURE_ID_RED_GIANT_STAR = "_red_giant_star";
const string VoidGenerator::FEATURE_ID_SUPERNOVA = "_supernova";
const string VoidGenerator::FEATURE_ID_BLACK_HOLE = "_black_hole";
const string VoidGenerator::FEATURE_ID_PULSAR = "_pulsar";

const int VoidGenerator::PCT_CHANCE_SPACE_DUST = 40;
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
    // ...
  }
}

void VoidGenerator::add_celestial_objects(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    // ...
  }
}

void VoidGenerator::add_spiral_arm(MapPtr result_map)
{
  if (result_map != nullptr)
  {
    // ...
  }
}
