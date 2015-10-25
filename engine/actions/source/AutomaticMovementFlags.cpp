#include "AutomaticMovementFlags.hpp"

AutomaticMovementFlags::AutomaticMovementFlags(const bool ignore_item_checks, const bool ignore_tile_checks, const bool ignore_prev_visited_checks, const bool ignore_feature_checks)
: ignore_items(ignore_item_checks), ignore_tile(ignore_tile_checks), ignore_prev_visited(ignore_prev_visited_checks), ignore_feature(ignore_feature_checks)
{
}

bool AutomaticMovementFlags::get_ignore_items() const
{
  return ignore_items;
}

bool AutomaticMovementFlags::get_ignore_tile() const
{
  return ignore_tile;
}

bool AutomaticMovementFlags::get_ignore_prev_visited() const
{
  return ignore_prev_visited;
}

bool AutomaticMovementFlags::get_ignore_feature() const
{
  return ignore_feature;
}

#ifdef UNIT_TESTS
#include "unit_tests/AutomaticMovementFlags_test.cpp"
#endif
