#include "ScrubTile.hpp"

TileType ScrubTile::get_tile_type() const
{
  return TileType::TILE_TYPE_SCRUB;
}

std::string ScrubTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_SCRUB;
}

Tile* ScrubTile::clone()
{
  return new ScrubTile(*this);
}

ClassIdentifier ScrubTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCRUB_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScrubTile_test.cpp"
#endif
