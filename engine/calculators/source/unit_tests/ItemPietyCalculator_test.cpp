#include "gtest/gtest.h"
#include "Amulet.hpp"

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

TEST(SL_Engine_Calculators_ItemPietyCalculator, minimum_piety)
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
}

TEST(SL_Engine_Calculators_ItemPietyCalculator, calculated_piety_value)
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