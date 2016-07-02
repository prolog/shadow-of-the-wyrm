#include "WorldMapTile.hpp"

WorldMapTile::WorldMapTile()
: Tile()
{
}

WorldMapTile::WorldMapTile(const DigChances& dc)
: Tile(dc)
{
}

bool WorldMapTile::display_description_on_arrival() const
{
  return false;
}

ClassIdentifier WorldMapTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WORLD_MAP_TILE;
}

bool WorldMapLandmarkTile::display_description_on_arrival() const
{
  return true;
}

ClassIdentifier WorldMapLandmarkTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WORLD_MAP_LANDMARK_TILE;
}