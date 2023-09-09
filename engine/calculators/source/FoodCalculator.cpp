#include "FoodCalculator.hpp"
#include "Consumable.hpp"

int FoodCalculator::calculate_nutrition(ItemPtr item) const
{
	int nutr = 0;

	if (item != nullptr)
	{
		ConsumablePtr consumable = std::dynamic_pointer_cast<Consumable>(item);

		if (consumable != nullptr)
		{
			int base_nutr = consumable->get_nutrition();
			ItemStatus status = consumable->get_status();
			float mult = get_item_status_multiplier(status);
			
			nutr = static_cast<int>(base_nutr * mult);
		}
	}

	return nutr;
}

float FoodCalculator::get_item_status_multiplier(const ItemStatus status) const
{
	switch (status)
	{
		case ItemStatus::ITEM_STATUS_BLESSED:
			return 1.25f;
		case ItemStatus::ITEM_STATUS_CURSED:
			return 0.5f;
		case ItemStatus::ITEM_STATUS_UNCURSED:
		default:
			return 1.0f;
	}
}

#ifdef UNIT_TESTS
#include "unit_tests/FoodCalculator_test.cpp"
#endif
