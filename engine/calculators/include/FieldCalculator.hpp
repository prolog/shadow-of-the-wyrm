#pragma once
#include "common.hpp"
#include "Creature.hpp"

class FieldCalculator
{
	public:
		int calc_pct_chance_wild_grains(CreaturePtr creature, const int world_height, const Coordinate& world_map_pos) const;
};
