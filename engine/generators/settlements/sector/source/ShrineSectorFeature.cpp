#include "ShrineSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "DeityUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "SettlementGeneratorUtils.hpp"

using namespace std;

bool ShrineSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    CardinalDirection door_dir = CardinalDirection::CARDINAL_DIRECTION_NORTH;
    
    if (RNG::percent_chance(50))
    {
      door_dir = CardinalDirection::CARDINAL_DIRECTION_SOUTH;
    }
    
    pair<int, int> door_loc = SettlementGeneratorUtils::get_door_location(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir);
 
    GeneratorUtils::generate_building(map, start_coord.first, start_coord.second, end_coord.first-start_coord.first+1, end_coord.second-start_coord.second+1);
    GeneratorUtils::generate_door(map, door_loc.first, door_loc.second);

    generate_altar(map, start_coord, end_coord);
    generate_building_features(map, start_coord, end_coord);

    generated = true;
  }

  return generated;
}

void ShrineSectorFeature::generate_altar(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    Coordinate altar_loc = CoordUtils::get_centre_coordinate(start_coord, end_coord);
    TilePtr tile = map->at(altar_loc);

    if (tile && !tile->has_feature())
    {
      pair<DeityPtr, AlignmentRange> deity_details = DeityUtils::get_random_deity_with_align(Game::instance());
      DeityPtr deity = deity_details.first;

      if (deity != nullptr)
      {
        FeaturePtr altar = FeatureGenerator::generate_altar(deity->get_id(), deity->get_alignment_range());
        tile->set_feature(altar);
      }
    }
  }
}

void ShrineSectorFeature::generate_building_features(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    Coordinate fstart_coord = {start_coord.first + 1, start_coord.second + 1};
    Coordinate fend_coord = {end_coord.first - 1, end_coord.second - 1};

    vector<Coordinate> corners = CoordUtils::get_corner_coordinates(fstart_coord, fend_coord);
    vector<ClassIdentifier> feature_types = {ClassIdentifier::CLASS_ID_PEW, ClassIdentifier::CLASS_ID_SARCOPHAGUS, ClassIdentifier::CLASS_ID_FIRE_PILLAR, ClassIdentifier::CLASS_ID_STONE_MARKER, ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE, ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE};
    ClassIdentifier feat = feature_types.at(RNG::range(0, feature_types.size()-1));

    for (const Coordinate& c : corners)
    {
      FeaturePtr feature = FeatureGenerator::create_feature(feat);
      TilePtr tile = map->at(c);

      if (tile && !tile->has_feature())
      {
        tile->set_feature(feature);
      }
    }
  }
}