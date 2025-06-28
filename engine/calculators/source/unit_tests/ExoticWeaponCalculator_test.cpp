#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_ExoticWeaponCalculator, get_base_difficulty)
{
	ExoticWeaponCalculator ewc;
	
	EXPECT_EQ(15, ewc.get_base_difficulty_for_improvised_exotic_weapon());
}

TEST(SW_Engine_Calculators_ExoticWeaponCalculator, get_base_speed)
{
	ExoticWeaponCalculator ewc;
	
	EXPECT_EQ(4, ewc.get_base_speed_for_improvised_exotic_weapon());
}

TEST(SW_Engine_Calculator_ExoticWeaponCalculator, get_base_damage)
{
	ExoticWeaponCalculator ewc;
	Damage dam = ewc.get_base_damage_for_improvised_exotic_weapon();

	EXPECT_EQ(static_cast<uint>(1), dam.get_num_dice());
	EXPECT_EQ(static_cast<uint>(2), dam.get_dice_sides());
	EXPECT_EQ(0, dam.get_modifier());
}

TEST(SW_Engine_Calculators_ExoticWeaponCalculator, get_general_modifier)
{
	ExoticWeaponCalculator ewc;
	std::map<int, int> mods = { {0, 0}, {3, 1}, {5, 1}, {6, 2}, {99, 33} };

	for (const auto& m_pair : mods)
	{
		EXPECT_EQ(m_pair.second, ewc.get_general_modifier(m_pair.first));
	}
}
