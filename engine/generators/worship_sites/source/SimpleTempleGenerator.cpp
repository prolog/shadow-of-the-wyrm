#include "FeatureGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "SimpleTempleGenerator.hpp"

using std::string;

SimpleTempleGenerator::SimpleTempleGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
{
}

MapPtr SimpleTempleGenerator::generate(const Dimensions& dim)
{
  return generate();
}

// Generate the simple, open-air temple and its features
MapPtr SimpleTempleGenerator::generate()
{
  MapPtr map = MapPtr(new Map(*base_map));
  
  generate_temple(map);

  return map;
}

// Generate the temple
void SimpleTempleGenerator::generate_temple(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int dais_size = RNG::range(3, 5);
  if (dais_size % 2 == 0) dais_size--;
  
  // Most of the temples are centred.  The Tricker's temples are very low-key and understated,
  // so they can appear anywhere on the map.  They almost appear as an afterthought - they're
  // never intended to be the centre of attention.
  int dais_start_row = RNG::range(2, rows-dais_size-2);
  int dais_start_col = RNG::range(2, cols-dais_size-2);

  TilePtr dais_tile;
  for (int row = dais_start_row; row < (dais_start_row + dais_size); row++)
  {
    for (int col = dais_start_col; col < (dais_start_col + dais_size); col++)
    {
      dais_tile = TileGenerator::generate(TILE_TYPE_DAIS);
      map->insert(row, col, dais_tile);
    }
  }

  generate_temple_features(map, dais_start_row, dais_start_col, dais_size);
}

// Generate the altar and the small pillars of flame around the dais.
void SimpleTempleGenerator::generate_temple_features(MapPtr map, const int dais_start_row, const int dais_start_col, const int dais_size)
{
  // Altar
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_NEUTRAL);
  TilePtr altar_tile = map->at((dais_start_row + (dais_start_row + dais_size)) / 2, (dais_start_col + (dais_start_col + dais_size)) / 2);
  altar_tile->set_feature(altar);

  // Pillars of flame
  FeaturePtr fire_pillar;
  TilePtr pillar_tile;
 
  // Top left
  pillar_tile = map->at(dais_start_row-1, dais_start_col-1);
  fire_pillar = FeatureGenerator::generate_fire_pillar();
  pillar_tile->set_feature(fire_pillar);
  
  // Top right
  pillar_tile = map->at(dais_start_row-1, dais_start_col+dais_size);
  fire_pillar = FeatureGenerator::generate_fire_pillar();
  pillar_tile->set_feature(fire_pillar);
  
  // Bottom left
  pillar_tile = map->at(dais_start_row+dais_size, dais_start_col-1);
  fire_pillar = FeatureGenerator::generate_fire_pillar();
  pillar_tile->set_feature(fire_pillar);
  
  // Bottom right
  pillar_tile = map->at(dais_start_row+dais_size, dais_start_col+dais_size);
  fire_pillar = FeatureGenerator::generate_fire_pillar();
  pillar_tile->set_feature(fire_pillar);
}

