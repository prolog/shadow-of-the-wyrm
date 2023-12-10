#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Food.hpp"

TEST(SW_Engine_Calculators_FoodCalculator, calculate_nutrition)
{
	FoodCalculator fc;

	ItemPtr amulet = std::make_shared<Amulet>();

	EXPECT_EQ(0, fc.calculate_nutrition(nullptr));
	EXPECT_EQ(0, fc.calculate_nutrition(amulet));

	ConsumablePtr food = std::make_shared<Food>();
	food->set_nutrition(100);

	std::map<ItemStatus, int> nutrition_map = { {ItemStatus::ITEM_STATUS_CURSED, 50}, {ItemStatus::ITEM_STATUS_UNCURSED, 100}, {ItemStatus::ITEM_STATUS_BLESSED, 125} };

	for (const auto& n_pair : nutrition_map)
	{
		food->set_status(n_pair.first);
		EXPECT_EQ(n_pair.second, fc.calculate_nutrition(food));
	}
}