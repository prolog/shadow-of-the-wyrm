#include "gtest/gtest.h"

class SL_Engine_Combat_CombatManager : public ::testing::Test
{
  protected:
    static void SetUpTestCase() {}
    static void TearDownTestcase() {}
    
    bool is_hit(const int total_roll, const int target_number_value) { return cm.is_hit(total_roll, target_number_value); }
    bool is_mighty_blow(const int d100_roll) { return cm.is_mighty_blow(d100_roll); }
    bool is_critical_hit(const int d100_roll) { return cm.is_critical_hit(d100_roll); }
    bool is_miss(const int total_roll, const int target_value) { return cm.is_miss(total_roll, target_value); }
    bool is_close_miss(const int total_roll, const int target_number_value) { return cm.is_close_miss(total_roll, target_number_value); }
    bool is_automatic_miss(const int d100_roll) { return cm.is_automatic_miss(d100_roll); }

    CombatManager cm;
};

TEST_F(SL_Engine_Combat_CombatManager, is_hit)
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

TEST_F(SL_Engine_Combat_CombatManager, is_critical_hit)
{
  int i = CombatConstants::CRITICAL_DIFFICULTY;
  
  EXPECT_TRUE(is_critical_hit(i));
  
  i--;
  
  EXPECT_FALSE(is_critical_hit(i));
  
  i -= 15;
  
  EXPECT_FALSE(is_critical_hit(i));
}

TEST_F(SL_Engine_Combat_CombatManager, is_mighty_blow)
{
  for (int i = CombatConstants::MIGHTY_BLOW_DIFFICULTY; i < CombatConstants::CRITICAL_DIFFICULTY; i++)
  {
    EXPECT_TRUE(is_mighty_blow(i));
  }
}

TEST_F(SL_Engine_Combat_CombatManager, is_miss)
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

TEST_F(SL_Engine_Combat_CombatManager, is_close_miss)
{
  int total_roll = 51;
  int target_number_value = 50;

  EXPECT_FALSE(is_close_miss(total_roll, target_number_value));
  
  total_roll--;

  int roll;
  int i;
  for (i = 0; i <= CombatConstants::CLOSE_MISS_THRESHOLD; i++)
  {
    roll = total_roll - i;
    EXPECT_TRUE(is_close_miss(roll, target_number_value));
  }
  
  roll = total_roll - CombatConstants::CLOSE_MISS_THRESHOLD - 1;
  
  EXPECT_FALSE(is_close_miss(roll, target_number_value));
}

TEST_F(SL_Engine_Combat_CombatManager, is_automatic_miss)
{
  int i;
  for (i = 0; i <= CombatConstants::AUTOMATIC_MISS_THRESHOLD; i++)
  {
    EXPECT_TRUE(is_automatic_miss(i));
  }
  
  i = CombatConstants::AUTOMATIC_MISS_THRESHOLD + 1;
  
  EXPECT_FALSE(is_automatic_miss(i));
}
