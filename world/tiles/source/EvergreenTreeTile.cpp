#include "EvergreenTreeTile.hpp"

using namespace std;

TileType EvergreenTreeTile::get_tile_type() const
{
  return TileType::TILE_TYPE_EVERGREEN_TREE;
}

string EvergreenTreeTile::get_default_tree_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_EVERGREEN_TREE;
}

Tile* EvergreenTreeTile::clone()
{
  return new EvergreenTreeTile(*this);
}

ClassIdentifier EvergreenTreeTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EVERGREEN_TREE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvergreenTreeTile_test.cpp"
#endif
