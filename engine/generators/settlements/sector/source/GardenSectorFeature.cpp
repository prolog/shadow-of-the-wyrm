#include "GardenSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

GardenSectorFeature::GardenSectorFeature(const string& new_deity_id, const AlignmentRange new_ar)
: deity_id(new_deity_id), alignment_range(new_ar)
{
}

string GardenSectorFeature::get_deity_id() const
{
  return deity_id;
}

bool GardenSectorFeature::has_altar() const
{
  return (deity_id.empty() == false);
}

AlignmentRange GardenSectorFeature::get_alignment_range() const
{
  return alignment_range;
}

bool GardenSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;
  generated = generate_garden(map, start_coord, end_coord);

  if (generated && map != nullptr && has_altar())
  {
    Dimensions dim = map->size();
    Coordinate centre = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    vector<Coordinate> adj_centre = CoordUtils::get_adjacent_map_coordinates(dim, centre.first, centre.second);
    TileGenerator tg;

    // Clear some space for quiet reflection.
    for (const Coordinate& ac : adj_centre)
    {
      TilePtr field = tg.generate(TileType::TILE_TYPE_FIELD);
      map->insert(ac, field);
    }

    // Place the altar in the centre.
    FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, alignment_range);
    TilePtr centre_tile = map->at(centre);

    if (centre_tile != nullptr)
    {
      centre_tile->get_items()->clear();
      centre_tile->set_feature(altar);
    }
  }

  return generated;
}
