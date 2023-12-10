#pragma once
#include "Damage.hpp"

class ExoticWeaponCalculator
{
	public:
		int get_base_difficulty_for_improvised_exotic_weapon() const;
		int get_base_speed_for_improvised_exotic_weapon() const;
		Damage get_base_damage_for_improvised_exotic_weapon() const;
		int get_general_modifier(const double weight_in_lbs) const;

	protected:
		static const int EXOTIC_WEAPON_BASE_DIFFICULTY;
		static const int EXOTIC_WEAPON_BASE_SPEED;
		static const int GENERAL_MODIFIER_DIVISOR;
};