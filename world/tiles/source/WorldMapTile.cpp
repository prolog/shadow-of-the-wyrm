#include "WorldMapTile.hpp"

WorldMapTile::WorldMapTile()
: Tile()
{
}

bool WorldMapTile::display_description_on_arrival() const
{
  return false;
}

ClassIdentifier WorldMapTile::internal_class_identifier() const
{
  return CLASS_ID_WORLD_MAP_TILE;
}

WorldMapLandmarkTile::WorldMapLandmarkTile()
: WorldMapTile()
{
}

bool WorldMapLandmarkTile::display_description_on_arrival() const
{
  return true;
}

ClassIdentifier WorldMapLandmarkTile::internal_class_identifier() const
{
  return CLASS_ID_WORLD_MAP_LANDMARK_TILE;
}