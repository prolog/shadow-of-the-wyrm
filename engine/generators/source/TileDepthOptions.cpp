#include "TileDepthOptions.hpp"

using namespace std;

TileDepthOptions::TileDepthOptions()
: min_depth(1), max_depth(1)
{
}

TileDepthOptions::TileDepthOptions(const int new_min_depth, const int new_max_depth, const vector<int>& new_remaining_depths)
: min_depth(new_min_depth), max_depth(new_max_depth), remaining_depths(new_remaining_depths)
{
}

void TileDepthOptions::set_min_depth(const int new_min_depth)
{
  min_depth = new_min_depth;
}

int TileDepthOptions::get_min_depth() const
{
  return min_depth;
}

void TileDepthOptions::set_max_depth(const int new_max_depth)
{
  max_depth = new_max_depth;
}

int TileDepthOptions::get_max_depth() const
{
  return max_depth;
}

void TileDepthOptions::set_remaining_depths(const vector<int>& new_remaining_depths)
{
  remaining_depths = new_remaining_depths;
}

vector<int>& TileDepthOptions::get_remaining_depths_ref()
{
  return remaining_depths;
}

vector<int> TileDepthOptions::get_remaining_depths() const
{
  return remaining_depths;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileDepthOptions_test.cpp"
#endif

