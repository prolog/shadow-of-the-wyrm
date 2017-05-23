#include "TileUtils.hpp"
#include "GraveTile.hpp"

using namespace std;

TileUtils::TileUtils()
{
}

TileUtils::~TileUtils()
{
}

// The "opposite" tile type really only makes sense for staircase tiles,
// where the opposite of an up staircase is a down staircase, and vice
// versa.  For every other tile type, the opposite is the tile type
// provided as a parameter.
TileType TileUtils::get_opposite_tile_type(const TileType tt)
{
  if (tt == TileType::TILE_TYPE_UP_STAIRCASE)
  {
    return TileType::TILE_TYPE_DOWN_STAIRCASE;
  }
  else if (tt == TileType::TILE_TYPE_DOWN_STAIRCASE)
  {
    return TileType::TILE_TYPE_UP_STAIRCASE;
  }

  return tt;
}

void TileUtils::set_grave_feature(TilePtr tile, FeaturePtr grave_feature)
{
  if (tile != nullptr && grave_feature != nullptr)
  {
    GraveTile gt;
    DigChances dc = gt.get_dig_chances();

    tile->set_dig_chances(dc);
    tile->set_feature(grave_feature);
  }
}

void TileUtils::copy_exit_properties_to_tile(TilePtr tile)
{
  if (tile != nullptr)
  {
    TileExitMap& exits = tile->get_tile_exit_map_ref();

    for (const auto& t_pair : exits)
    {
      MapExitPtr exit = t_pair.second;

      if (exit != nullptr)
      {
        map<string, string> properties = exit->get_properties();

        for (const auto& p_pair : properties)
        {
          tile->set_additional_property(p_pair.first, p_pair.second);
        }
      }
    }
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/TileUtils_test.cpp"
#endif

