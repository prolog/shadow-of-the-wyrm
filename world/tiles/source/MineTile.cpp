#include "MineTile.hpp"

TileType MineTile::get_tile_type() const
{
  return TileType::TILE_TYPE_MINE;
}

std::string MineTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MINE;
}

Tile* MineTile::clone()
{
  return new MineTile(*this);
}

ClassIdentifier MineTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MINE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/MineTile_test.cpp"
#endif
