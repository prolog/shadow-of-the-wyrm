#include "gtest/gtest.h"
#include "Food.hpp"
TEST(SW_World_Consumable, consumable_properties_match)
{
  Food f1;
  Food f2;

  EXPECT_TRUE(f1.consumable_properties_match(f2));

  f1.set_nutrition(111);
  f2.set_nutrition(111);

  f1.set_standard_drinks(3);
  f2.set_standard_drinks(3);

  f1.set_food_type(FoodType::FOOD_TYPE_CARBS);
  f2.set_food_type(FoodType::FOOD_TYPE_CARBS);

  EXPECT_TRUE(f1.consumable_properties_match(f2));

  f2.set_nutrition(222);

  EXPECT_FALSE(f1.consumable_properties_match(f2));

  f2.set_nutrition(111);
  f2.set_standard_drinks(10);

  EXPECT_FALSE(f1.consumable_properties_match(f2));

  f2.set_standard_drinks(3);
  f2.set_food_type(FoodType::FOOD_TYPE_DAIRY);

  EXPECT_FALSE(f1.consumable_properties_match(f2));

  f2.set_food_type(FoodType::FOOD_TYPE_CARBS);
  f2.set_poisoned(true);
  
  EXPECT_FALSE(f1.consumable_properties_match(f2));
  
  f2.set_poisoned(false);
  
  EXPECT_TRUE(f1.consumable_properties_match(f2)); 
}

