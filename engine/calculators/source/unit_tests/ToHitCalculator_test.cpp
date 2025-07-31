#include "gtest/gtest.h"
#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"
#include "HeavyWeaponToHitCalculator.hpp"
#include "MagicToHitCalculator.hpp"
#include "WandsToHitCalculator.hpp"

TEST(SW_Engine_Calculators_ToHitCalculator, lore_skill_part)
{
	std::vector<ToHitCalculatorPtr> calcs;

	calcs.push_back(std::make_unique<LightMeleeAndRangedWeaponToHitCalculator>());
	calcs.push_back(std::make_unique<HeavyWeaponToHitCalculator>());
	calcs.push_back(std::make_unique<MagicToHitCalculator>());
	calcs.push_back(std::make_unique<WandsToHitCalculator>());

	CreaturePtr creature;
	MapPtr map;

	for (const auto& calc : calcs)
	{
		EXPECT_EQ(0, calc->calculate(creature, map));
	}
}