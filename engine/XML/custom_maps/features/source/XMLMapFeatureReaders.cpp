#include <vector>
#include "XMLMapCoordinateReader.hpp"
#include "XMLMapFeatureReaders.hpp"
#include "XMLMapFeatureFactory.hpp"

using namespace std;

// Parse all the features, and place them on the map.
void XMLMapFeaturesReader::parse_features(const XMLNode& features_node, MapPtr map)
{
  if (!features_node.is_null())
  {
    vector<XMLNode> feature_placement_nodes = XMLUtils::get_elements_by_local_name(features_node, "FeaturePlacement");

    for (const XMLNode& node : feature_placement_nodes)
    {
      parse_feature_placement(node, map);
    }
  }
}

// Parse an individual feature placement, and place it on the map.
void XMLMapFeaturesReader::parse_feature_placement(const XMLNode& feature_placement_node, MapPtr map)
{
  if (!feature_placement_node.is_null())
  {
    XMLNode coord_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Coord");

    XMLMapCoordinateReader coord_reader;
    Coordinate c = coord_reader.parse_fixed_coordinate(coord_node);

    FeaturePtr feature = XMLMapFeatureFactory::create_feature(feature_placement_node);
    TilePtr tile = map->at(c);

    if (tile && feature)
    {
      tile->set_feature(feature);
    }
  }
}