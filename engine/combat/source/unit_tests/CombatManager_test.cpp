#include "gtest/gtest.h"

class SW_Engine_Combat_CombatManager : public ::testing::Test
{
  protected:
    static void SetUpTestCase() {}
    static void TearDownTestcase() {}
    
    bool is_hit(const int total_roll, const int target_number_value) { return cm.is_hit(total_roll, target_number_value); }
    bool is_miss(const int total_roll, const int target_value) { return cm.is_miss(total_roll, target_value); }
    bool is_close_miss(const int total_roll, const int target_number_value) { return cm.is_close_miss(total_roll, target_number_value); }
    bool is_automatic_miss(const int d100_roll) { return cm.is_automatic_miss(d100_roll); }

    CombatManager cm;
};

TEST_F(SW_Engine_Combat_CombatManager, is_hit)
{
  int total_roll = 50;
  int target_number_value = 45;

  EXPECT_TRUE(is_hit(total_roll, target_number_value));
  
  total_roll = 45;
  
  EXPECT_FALSE(is_hit(total_roll, target_number_value));
  
  total_roll = 60;
  target_number_value = 10;
  
  EXPECT_TRUE(is_hit(total_roll, target_number_value));
}

TEST_F(SW_Engine_Combat_CombatManager, is_miss)
{
  int total_roll = 50;
  int target_number_value = 50;
  
  EXPECT_TRUE(is_miss(total_roll, target_number_value));
  
  total_roll++;
  
  EXPECT_FALSE(is_miss(total_roll, target_number_value));
  
  total_roll -= 10;
  
  EXPECT_TRUE(is_miss(total_roll, target_number_value));
  
  total_roll += 2;
  
  EXPECT_TRUE(is_miss(total_roll, target_number_value));
}

TEST_F(SW_Engine_Combat_CombatManager, is_close_miss)
{
  int target_number_value = 50;

  EXPECT_FALSE(is_close_miss(45, target_number_value));

  for (int i = 46; i <= 50; i++)
  {
    EXPECT_TRUE(is_close_miss(i, target_number_value));
  }

  for (int i = 51; i <= 55; i++)
  {
    EXPECT_FALSE(is_close_miss(i, target_number_value));
  }
}

TEST_F(SW_Engine_Combat_CombatManager, is_automatic_miss)
{
  int i;
  for (i = 0; i <= CombatConstants::AUTOMATIC_MISS_THRESHOLD; i++)
  {
    EXPECT_TRUE(is_automatic_miss(i));
  }
  
  i = CombatConstants::AUTOMATIC_MISS_THRESHOLD + 1;
  
  EXPECT_FALSE(is_automatic_miss(i));
}
