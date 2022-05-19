#include "DefaultMovementAccumulationChecker.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

void DefaultMovementAccumulationChecker::check(CreaturePtr creature)
{
	if (creature != nullptr)
	{
		MapPtr map = Game::instance().get_current_map();
		TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

		if (tile != nullptr)
		{
			mark_skills(creature, tile);
		}
	}
}

void DefaultMovementAccumulationChecker::mark_skills(CreaturePtr creature, TilePtr tile)
{
	if (creature != nullptr && tile != nullptr)
	{
		TileType tt = tile->get_tile_type();

		if (tt == TileType::TILE_TYPE_HILLS)
		{
			if (RNG::percent_chance(2))
			{
				creature->get_skills().mark(SkillType::SKILL_GENERAL_MOUNTAINEERING);
			}
		}
	}
}
