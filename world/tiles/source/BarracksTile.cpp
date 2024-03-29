#include "BarracksTile.hpp"

TileType BarracksTile::get_tile_type() const
{
  return TileType::TILE_TYPE_BARRACKS;
}

std::string BarracksTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_BARRACKS;
}

bool BarracksTile::is_interior() const
{
  return true;
}

Tile* BarracksTile::clone()
{
  return new BarracksTile(*this);
}

ClassIdentifier BarracksTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BARRACKS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/BarracksTile_test.cpp"
#endif