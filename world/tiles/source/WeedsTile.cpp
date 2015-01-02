#include "WeedsTile.hpp"

TileType WeedsTile::get_tile_type() const
{
  return TILE_TYPE_WEEDS;
}

std::string WeedsTile::get_default_tree_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WEEDS;
}

Tile* WeedsTile::clone()
{
  return new WeedsTile(*this);
}

ClassIdentifier WeedsTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WEEDS_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/WeedsTile_test.cpp"
#endif
