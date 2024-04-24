#include "WeedsTile.hpp"

using namespace std;

TileType WeedsTile::get_tile_type() const
{
  return TileType::TILE_TYPE_WEEDS;
}

vector<pair<pair<int, int>, std::string>> WeedsTile::get_decomposition_item_ids() const
{
  return {};
}


std::string WeedsTile::get_default_tree_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_WEEDS;
}

std::string WeedsTile::get_dig_message_sid() const
{
  return TileTextKeys::TILE_DIG_WEEDS;
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
