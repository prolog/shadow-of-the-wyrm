#include "TreeTile.hpp"

using namespace std;

TileType TreeTile::get_tile_type() const
{
  return TileType::TILE_TYPE_TREE;
}

std::string TreeTile::get_tile_description_sid() const
{
  string tile_desc_sid = get_additional_property(TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID);

  if (!tile_desc_sid.empty())
  {
    return tile_desc_sid;
  }

  return get_default_tree_tile_description_sid();
}

std::string TreeTile::get_default_tree_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_TREE;
}

TileType TreeTile::get_decomposition_tile_type() const
{
  return TileType::TILE_TYPE_FIELD;
}

vector<pair<pair<int, int>, std::string>> TreeTile::get_decomposition_item_ids() const
{
  vector<pair<pair<int, int>, string>> decomp_ids = { {{2,3}, ItemIdKeys::ITEM_ID_LUMBER},
                                                      {{2,3}, ItemIdKeys::ITEM_ID_BOUGH},
                                                      {{2,3}, ItemIdKeys::ITEM_ID_BRANCH} };

  return decomp_ids;
}

Tile* TreeTile::clone()
{
  return new TreeTile(*this);
}

ClassIdentifier TreeTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TREE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/TreeTile_test.cpp"
#endif
