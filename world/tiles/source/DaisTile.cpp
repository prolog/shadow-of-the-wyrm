#include "DaisTile.hpp"

// Individual raised floor tiles
TileType DaisTile::get_tile_type() const
{
  return TILE_TYPE_DAIS;
}

std::string DaisTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_DAIS;
}

Tile* DaisTile::clone()
{
  return new DaisTile(*this);
}

ClassIdentifier DaisTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DAIS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/DaisTile_test.cpp"
#endif
