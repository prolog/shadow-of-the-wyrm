#pragma once
#include "Map.hpp"

class TerrainSpeedMultiplierCalculator
{
	public:
		float calculate(CreaturePtr creature, MapPtr map) const;

	protected:
		float calculate_for_tile_type(CreaturePtr creature, const TileType tt) const;
		float calculate_for_super_type(CreaturePtr creature, const TileSuperType tst, const bool is_submerged) const;
		float calculate_for_water(CreaturePtr creature, const bool is_submerged) const;

		static const int BOATING_DIVISOR;
};
