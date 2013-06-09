#include "FruitTreeTile.hpp"

TileType FruitTreeTile::get_tile_type() const
{
  return TILE_TYPE_FRUIT_TREE;
}

std::string FruitTreeTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_FRUIT_TREE;
}

Tile* FruitTreeTile::clone()
{
  return new FruitTreeTile(*this);
}

ClassIdentifier FruitTreeTile::internal_class_identifier() const
{
  return CLASS_ID_FRUIT_TREE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/FruitTreeTile_test.cpp"
#endif
