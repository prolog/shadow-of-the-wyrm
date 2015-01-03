#include "HillsTile.hpp"

TileType HillsTile::get_tile_type() const
{
  return TileType::TILE_TYPE_HILLS;
}

std::string HillsTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_HILLS;
}

Tile* HillsTile::clone()
{
  return new HillsTile(*this);
}

ClassIdentifier HillsTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HILLS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/HillsTile_test.cpp"
#endif
