#include "MagicalTreeTile.hpp"

using namespace std;

TileType MagicalTreeTile::get_tile_type() const
{
  return TileType::TILE_TYPE_MAGICAL_TREE;
}

string MagicalTreeTile::get_default_tree_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_MAGICAL_TREE;
}

Tile* MagicalTreeTile::clone()
{
  return new MagicalTreeTile(*this);
}

ClassIdentifier MagicalTreeTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAGICAL_TREE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicalTreeTile_test.cpp"
#endif
