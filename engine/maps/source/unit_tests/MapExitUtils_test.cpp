#include "gtest/gtest.h"

class SL_Engine_Maps_MapExitUtilsFixture : public ::testing::Test
{
  protected:
    void add_map_tile_exit(map<Direction, vector<Coordinate>>& tile_exits, const Direction d, const Coordinate& c);
};

void SL_Engine_Maps_MapExitUtilsFixture::add_map_tile_exit(map<Direction, vector<Coordinate>>& tile_exits, const Direction d, const Coordinate& c)
{
  MapExitUtils::add_map_tile_exit(tile_exits, d, c);
}

// Ensure that:
//
// - When a map doesn't have a mapping for a direction, one is added
TEST_F(SL_Engine_Maps_MapExitUtilsFixture, map_tile_exit_added_new_dir)
{
  Coordinate tile_coord(3,4);
  Direction direction = Direction::DIRECTION_SOUTH;
  map<Direction, vector<Coordinate>> tile_exits;

  add_map_tile_exit(tile_exits, direction, tile_coord);

  EXPECT_EQ(1, tile_exits.size());

  auto m_it = tile_exits.find(direction);

  EXPECT_TRUE(m_it != tile_exits.end());

  if (m_it != tile_exits.end())
  {
    vector<Coordinate> c = m_it->second;

    EXPECT_EQ(1, c.size());

    EXPECT_EQ(tile_coord, c.at(0));
  }
}

TEST_F(SL_Engine_Maps_MapExitUtilsFixture, map_tile_exit_added_to_existing)
{
  Coordinate tile_coord(3,2);
  Direction direction = Direction::DIRECTION_SOUTH_EAST;
  map<Direction, vector<Coordinate>> tile_exits;
  tile_exits.insert(make_pair(direction, vector<Coordinate>{tile_coord}));

  Coordinate new_coord(5,7);

  add_map_tile_exit(tile_exits, direction, new_coord);

  auto m_it = tile_exits.find(direction);

  EXPECT_EQ(2, m_it->second.size());

  // Ensure a particular set of coordinates exists only once for a
  // given direction.
  add_map_tile_exit(tile_exits, direction, new_coord);

  m_it = tile_exits.find(direction);

  EXPECT_EQ(2, m_it->second.size());
}
