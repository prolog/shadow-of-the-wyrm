#include "gtest/gtest.h"

TEST(SW_Engine_Generators_Settlements_Building, exterior_coords)
{
  Building b({5, 5}, {7, 7}, {});

  pair<Coordinate, Coordinate> exp = make_pair(make_pair(5,5), make_pair(7,7));
  
  EXPECT_EQ(exp, b.get_coords());

  Building b2({18, 6}, {22, 13}, {});

  exp = make_pair(make_pair(18,6), make_pair(22, 13));

  EXPECT_EQ(exp, b2.get_coords());
}

TEST(SW_Engine_Generators_Settlements_Building, interior_coords)
{
  Building b({5, 5}, {7, 7}, {});

  pair<Coordinate, Coordinate> exp = make_pair(make_pair(6, 6), make_pair(6, 6));

  EXPECT_EQ(exp, b.get_interior_coords());

  Building b2({18, 6}, {22, 13}, {});

  exp = make_pair(make_pair(19, 7), make_pair(21, 12));

  EXPECT_EQ(exp, b2.get_interior_coords());
}

TEST(SW_Engine_Generators_Settlements_Buildings, door_location)
{
  Building b{{5,5}, {7,7}, {5,6}};

  EXPECT_EQ(make_pair(5,6), b.get_door_coord());
}