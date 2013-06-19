#include "TreeTile.hpp"

using namespace std;

TileType TreeTile::get_tile_type() const
{
  return TILE_TYPE_TREE;
}

std::string TreeTile::get_tile_description_sid() const
{
  string tile_desc_sid = get_additional_property(TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID);

  if (!tile_desc_sid.empty())
  {
    return tile_desc_sid;
  }

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
