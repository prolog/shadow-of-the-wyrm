#include "TerrainSpeedMultiplierCalculator.hpp"

const int TerrainSpeedMultiplierCalculator::BOATING_DIVISOR = 2;

float TerrainSpeedMultiplierCalculator::calculate(CreaturePtr creature, MapPtr map) const
{
	float mult = 1.0f;

	if (creature != nullptr && map != nullptr)
	{
		TilePtr tile = map->at(map->get_location(creature->get_id()));

		if (tile != nullptr)
		{
			TileSuperType tst = tile->get_tile_super_type();

			mult *= calculate_for_tile_type(creature, tile->get_tile_type());
			mult *= calculate_for_super_type(creature, tile->get_tile_super_type(), tile->get_submerged());
		}
	}

	return mult;
}

float TerrainSpeedMultiplierCalculator::calculate_for_tile_type(CreaturePtr creature, const TileType tt) const
{
	return 1.0;
}

float TerrainSpeedMultiplierCalculator::calculate_for_super_type(CreaturePtr creature, const TileSuperType tst, const bool is_submerged) const
{
	float mult = 1.0f;

	if (creature != nullptr)
	{
		switch (tst) {
			case TileSuperType::TILE_SUPER_TYPE_WATER:
				mult = calculate_for_water(creature, is_submerged);
				break;
			case TileSuperType::TILE_SUPER_TYPE_AIR:
			case TileSuperType::TILE_SUPER_TYPE_GROUND:
			default:
				break;

		}
	}

	return mult;
}

float TerrainSpeedMultiplierCalculator::calculate_for_water(CreaturePtr creature, const bool is_submerged) const
{
	float mult = 1.0f;

	if (creature != nullptr && 
		  !is_submerged &&
		  !creature->has_status(StatusIdentifiers::STATUS_ID_FLYING) &&
		  creature->get_inventory()->has_item_type(ItemType::ITEM_TYPE_BOAT))
	{
		int boating = creature->get_skills().get_value(SkillType::SKILL_GENERAL_BOATING);
		boating /= BOATING_DIVISOR;

		mult -= (static_cast<float>(boating) / 100.0f);
	}

	return mult;
}

#ifdef UNIT_TESTS
#include "unit_tests/TerrainSpeedMultiplierCalculator_test.cpp"
#endif
