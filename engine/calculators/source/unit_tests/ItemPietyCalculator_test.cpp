#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Food.hpp"

float get_test_level_multiplier(const int creature_level);
float get_test_level_multiplier(const int creature_level)
{
  return 0.25f + (static_cast<float>(creature_level) / static_cast<float>(CreatureConstants::MAX_CREATURE_LEVEL));
}

class ItemPietyCalculatorTestFixture : public ::testing::Test
{
  public:
    int get_base_divisor(ItemPtr item);
    int get_base_value(ItemPtr item);
};

int ItemPietyCalculatorTestFixture::get_base_divisor(ItemPtr item)
{
  ItemPietyCalculator ipc;

  return ipc.get_base_divisor(item);
}

int ItemPietyCalculatorTestFixture::get_base_value(ItemPtr item)
{
  ItemPietyCalculator ipc;

  return ipc.get_base_value(item);
}

TEST(SW_Engine_Calculators_ItemPietyCalculator, minimum_piety)
{
  ItemPtr item = std::make_shared<Amulet>();
  item->set_value(1);

  ItemPietyCalculator ipc;

  EXPECT_EQ(0, ipc.calculate_piety(item));
}

TEST_F(ItemPietyCalculatorTestFixture, get_base_divisor)
{
  ItemPtr item = std::make_shared<Amulet>();
  item->set_value(1);

  EXPECT_EQ(10, get_base_divisor(item));
}

TEST_F(ItemPietyCalculatorTestFixture, get_base_value)
{
  ItemPtr item = std::make_shared<Amulet>();
  item->set_value(1);

  EXPECT_EQ(1, get_base_value(item));

  FoodPtr food = std::make_shared<Food>();
  food->set_nutrition(2000);

  EXPECT_EQ(1739, get_base_value(food));
}

TEST(SW_Engine_Calculators_ItemPietyCalculator, calculated_piety_value)
{
  ItemPietyCalculator ipc;
  ItemPtr item = std::make_shared<Amulet>();
  item->set_value(1);

  EXPECT_EQ(0, ipc.calculate_piety(item));

  item->set_value(1000);

  EXPECT_EQ(100, ipc.calculate_piety(item));

  item->set_quantity(3);

  EXPECT_EQ(300, ipc.calculate_piety(item));
}

TEST(SW_Engine_Calculators_ItemPietyCalculator, food_piety)
{
  ItemPietyCalculator ipc;
  FoodPtr food = std::make_shared<Food>();
  food->set_nutrition(800);

  // Doesn't meet min piety requirements
  EXPECT_EQ(0, ipc.calculate_piety(food));
}

TEST(SW_Engine_Calculators_ItemPietyCalculator, corpse_level_multiplier)
{
  ItemPietyCalculator ipc;
  FoodPtr corpse = std::make_shared<Food>();

  corpse->set_nutrition(3000);

  // When there's no race_id, it's just regular food and should get the
  // nutrition divisor applied.
  EXPECT_EQ(260, ipc.calculate_piety(corpse));

  corpse->set_additional_property(ConsumableConstants::CORPSE_RACE_ID, "01_human");

  // When there's no level, the multiplier should be 1.
  EXPECT_EQ(1000, ipc.calculate_piety(corpse));

  std::vector<int> corpse_level = { 1, 3, 17, 19, 38, 49, 50 };
  int exp_val = 0;

  for (const auto& cl : corpse_level)
  {
    corpse->set_additional_property(ConsumableConstants::CORPSE_LEVEL, std::to_string(cl));
    exp_val = static_cast<int>(1000 * get_test_level_multiplier(cl));
    
    EXPECT_EQ(exp_val, ipc.calculate_piety(corpse));
  }
}

TEST(ItemPietyCalculatorTest, piety_by_item_type)
{
  ItemPietyCalculator ipc;
  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_value(400);

  EXPECT_EQ(40, ipc.calculate_piety(amulet));

  FoodPtr food = std::make_shared<Food>();
  food->set_nutrition(3000);
  EXPECT_EQ(260, ipc.calculate_piety(food));

  FoodPtr corpse = std::make_shared<Food>();
  corpse->set_nutrition(3000);
  corpse->set_additional_property(ConsumableConstants::CORPSE_RACE_ID, "01_human");
  corpse->set_additional_property(ConsumableConstants::CORPSE_LEVEL, std::to_string(17));
  int exp_corpse_val = static_cast<int>(1000 * get_test_level_multiplier(17));

  EXPECT_EQ(exp_corpse_val, ipc.calculate_piety(corpse));
}
