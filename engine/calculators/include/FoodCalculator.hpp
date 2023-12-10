#pragma once
#include "Item.hpp"

class FoodCalculator
{
	public:
		int calculate_nutrition(ItemPtr item) const;

	protected:
		float get_item_status_multiplier(const ItemStatus status) const;
};