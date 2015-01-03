#include "CairnTile.hpp"

TileType CairnTile::get_tile_type() const
{
  return TileType::TILE_TYPE_CAIRN;
}

std::string CairnTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_CAIRN;
}

Tile* CairnTile::clone()
{
  return new CairnTile(*this);
}

ClassIdentifier CairnTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CAIRN_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/CairnTile_test.cpp"
#endif
