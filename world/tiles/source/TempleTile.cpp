#include "TempleTile.hpp"

// Needed for boost's serialization library
TempleTile::TempleTile()
{
  tile_subtype = TileType::TILE_TYPE_UNDEFINED;
}
 
TempleTile::TempleTile(const TileType subtype)
{
  tile_subtype = subtype;
}

TileType TempleTile::get_tile_type() const
{
  return TileType::TILE_TYPE_TEMPLE;
}

std::string TempleTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_TEMPLE;
}

Tile* TempleTile::clone()
{
  return new TempleTile(*this);
}

ClassIdentifier TempleTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_TEMPLE_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/TempleTile_test.cpp"
#endif