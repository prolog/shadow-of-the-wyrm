#include "WorldMapTile.hpp"

WorldMapTile::WorldMapTile()
: Tile()
{
}

bool WorldMapTile::display_description_on_arrival() const
{
  return false;
}

WorldMapLandmarkTile::WorldMapLandmarkTile()
: WorldMapTile()
{
}

bool WorldMapLandmarkTile::display_description_on_arrival() const
{
  return true;
}
