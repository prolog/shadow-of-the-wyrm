#include "ExoticWeaponCalculator.hpp"

const int ExoticWeaponCalculator::EXOTIC_WEAPON_BASE_DIFFICULTY = 15;
const int ExoticWeaponCalculator::EXOTIC_WEAPON_BASE_SPEED = 4;
const int ExoticWeaponCalculator::GENERAL_MODIFIER_DIVISOR = 3;

int ExoticWeaponCalculator::get_base_difficulty_for_improvised_exotic_weapon() const
{
	return EXOTIC_WEAPON_BASE_DIFFICULTY;
}

int ExoticWeaponCalculator::get_base_speed_for_improvised_exotic_weapon() const
{
	return EXOTIC_WEAPON_BASE_SPEED;
}

Damage ExoticWeaponCalculator::get_base_damage_for_improvised_exotic_weapon() const
{
	Damage d(1, 2, 0, DamageType::DAMAGE_TYPE_POUND, {}, false, false, false, false, false, false, false, false, 0, {});
	return d;
}

int ExoticWeaponCalculator::get_general_modifier(const double weight_in_lbs) const
{
	return static_cast<int>(weight_in_lbs / GENERAL_MODIFIER_DIVISOR);
}


#ifdef UNIT_TESTS
#include "unit_tests/ExoticWeaponCalculator_test.cpp"
#endif
