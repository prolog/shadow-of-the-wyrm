#include "gtest/gtest.h"

class LoadedMapDetailsTester : public ::testing::Test
{
  public:
    void test_update_map_id();
    void test_update_engine_coord();
    void test_update_display_coord();
    void test_update_blind_status();
    void test_update_season();
    void test_requires_full_redraw();

  private:
    LoadedMapDetails lmd;
    LoadedMapDetails lmd_def;
};

void test_set_various_values(LoadedMapDetails& lmd);
void test_set_various_values(LoadedMapDetails& lmd)
{
  lmd.update_map_id("foo");
  lmd.update_map_id("bar");

  Coordinate ec1(1,2);
  Coordinate ec2(2,2);
  lmd.update_engine_coord(ec1);
  lmd.update_engine_coord(ec2);

  Coordinate dc1(3,3);
  Coordinate dc2(3,4);
  lmd.update_display_coord(dc1);
  lmd.update_display_coord(dc2);

  lmd.update_blind_status(false);
  lmd.update_blind_status(true);

  lmd.update_season(Season::SEASON_WINTER);
  lmd.update_season(Season::SEASON_SPRING);
}

void LoadedMapDetailsTester::test_update_map_id()
{
  EXPECT_TRUE(lmd == lmd_def);

  lmd.update_map_id("test");

  EXPECT_FALSE(lmd == lmd_def);
  EXPECT_TRUE(lmd.cur_map_id == "test");

  lmd.update_map_id("test2");

  EXPECT_TRUE(lmd.prev_map_id == "test");
  EXPECT_TRUE(lmd.cur_map_id == "test2");
}

void LoadedMapDetailsTester::test_update_engine_coord()
{
  EXPECT_TRUE(lmd == lmd_def);

  Coordinate engine_c(2,3);
  lmd.update_engine_coord(engine_c);

  EXPECT_FALSE(lmd == lmd_def);
  EXPECT_TRUE(lmd.cur_engine_coord == engine_c);

  Coordinate engine_c2(2,4);
  lmd.update_engine_coord(engine_c2);
  EXPECT_TRUE(lmd.cur_engine_coord == engine_c2);
  EXPECT_TRUE(lmd.prev_engine_coord == engine_c);
}

void LoadedMapDetailsTester::test_update_display_coord()
{
  EXPECT_TRUE(lmd == lmd_def);

  Coordinate display_c(4, 7);
  lmd.update_display_coord(display_c);

  EXPECT_FALSE(lmd == lmd_def);
  EXPECT_TRUE(lmd.cur_display_coord == display_c);

  Coordinate display_c2(3,7);
  lmd.update_display_coord(display_c2);
  EXPECT_TRUE(lmd.cur_display_coord == display_c2);
  EXPECT_TRUE(lmd.prev_display_coord == display_c);
}

void LoadedMapDetailsTester::test_update_blind_status()
{
  EXPECT_TRUE(lmd == lmd_def);

  lmd.update_blind_status(true);

  EXPECT_FALSE(lmd == lmd_def);
  EXPECT_TRUE(lmd.cur_blind_status == true);

  lmd.update_blind_status(false);

  EXPECT_TRUE(lmd.prev_blind_status == true);
  EXPECT_TRUE(lmd.cur_blind_status == false);
}

void LoadedMapDetailsTester::test_update_season()
{
  EXPECT_TRUE(lmd == lmd_def);

  lmd.update_season(Season::SEASON_AUTUMN);

  EXPECT_FALSE(lmd == lmd_def);
  EXPECT_TRUE(lmd.cur_season == Season::SEASON_AUTUMN);

  lmd.update_season(Season::SEASON_WINTER);

  EXPECT_TRUE(lmd.prev_season == Season::SEASON_AUTUMN);
  EXPECT_TRUE(lmd.cur_season == Season::SEASON_WINTER);
}

void LoadedMapDetailsTester::test_requires_full_redraw()
{
  LoadedMapDetails lmd;

  test_set_various_values(lmd);

  EXPECT_TRUE(lmd.requires_full_map_redraw());

  lmd.synch();

  EXPECT_FALSE(lmd.requires_full_map_redraw());
}

TEST_F(LoadedMapDetailsTester, update_map_id)
{
  test_update_map_id();
}

TEST_F(LoadedMapDetailsTester, update_engine_coord)
{
  test_update_engine_coord();
}

TEST_F(LoadedMapDetailsTester, update_display_coord)
{
  test_update_display_coord();
}

TEST_F(LoadedMapDetailsTester, update_blind_status)
{
  test_update_blind_status();
}

TEST_F(LoadedMapDetailsTester, update_season)
{
  test_update_season();
}

TEST_F(LoadedMapDetailsTester, test_needs_redraw)
{
  test_requires_full_redraw();
}

TEST(SL_Engine_Maps_LoadedMapDetails, serialization_id)
{
  LoadedMapDetails lmd;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_LOADED_MAP_DETAILS, lmd.get_class_identifier());
}

TEST(SL_Engine_Maps_LoadedMapDetails, saveload)
{
  LoadedMapDetails lmd, lmd2;

  test_set_various_values(lmd);
  
  ostringstream oss;
  lmd.serialize(oss);

  istringstream iss(oss.str());
  lmd2.deserialize(iss);

  EXPECT_TRUE(lmd == lmd2);
}