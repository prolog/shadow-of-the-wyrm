#include "FieldCalculator.hpp"

// The chance to find wild grains is greater when closer to the equator.
// Creatures skilled in foraging will find more wild grain fields.
int FieldCalculator::calc_pct_chance_wild_grains(CreaturePtr creature, const int world_map_height, const Coordinate& world_map_pos) const
{
	int pct_chance = 0;

	int equator = world_map_height / 2;
	int row = world_map_pos.first;
	pct_chance = equator - std::abs(equator - row);

	if (creature != nullptr)
	{
		int foraging = creature->get_skills().get_value(SkillType::SKILL_GENERAL_FORAGING);
		pct_chance = std::max(pct_chance, foraging);
	}

	return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/FieldCalculator_test.cpp"
#endif
