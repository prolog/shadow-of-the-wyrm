#include "TreeTile.hpp"

TileType TreeTile::get_tile_type() const
{
  return TILE_TYPE_TREE;
}

std::string TreeTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_TREE;
}

Tile* TreeTile::clone()
{
  return new TreeTile(*this);
}

ClassIdentifier TreeTile::internal_class_identifier() const
{
  return CLASS_ID_TREE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/TreeTile_test.cpp"
#endif
