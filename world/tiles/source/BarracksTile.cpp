#include "BarracksTile.hpp"

TileType BarracksTile::get_tile_type() const
{
  return TILE_TYPE_BARRACKS;
}

std::string BarracksTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BARRACKS;
}

Tile* BarracksTile::clone()
{
  return new BarracksTile(*this);
}

ClassIdentifier BarracksTile::internal_class_identifier() const
{
  return CLASS_ID_BARRACKS_TILE;
}