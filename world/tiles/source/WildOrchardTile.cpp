#include "WildOrchardTile.hpp"

TileType WildOrchardTile::get_tile_type() const
{
  return TileType::TILE_TYPE_WILD_ORCHARD;
}

std::string WildOrchardTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WILD_ORCHARD;
}

Tile* WildOrchardTile::clone()
{
  return new WildOrchardTile(*this);
}

ClassIdentifier WildOrchardTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WILD_ORCHARD_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/WildOrchardTile_test.cpp"
#endif
