#include "EffectTypeTerrainChecker.hpp"

const int EffectTypeTerrainChecker::MIN_TERRAIN_COUNT_THRESHOLD = 3;

EffectTypeTerrainChecker::EffectTypeTerrainChecker()
	: applicable_tst({ {EffectType::EFFECT_TYPE_FLYING, TileSuperType::TILE_SUPER_TYPE_AIR}, 
										 {EffectType::EFFECT_TYPE_WATER_BREATHING, TileSuperType::TILE_SUPER_TYPE_WATER} })
{
}

bool EffectTypeTerrainChecker::does_effect_match_terrain(CreaturePtr caster, MapPtr view_map, const EffectType effect_type) const
{
	bool matches = false;
	int cnt = 0;

	if (caster != nullptr && view_map != nullptr)
	{
		auto t_it = applicable_tst.find(effect_type);

		if (t_it != applicable_tst.end())
		{
			TileSuperType tst = t_it->second;

			const TilesContainer& tc = view_map->get_tiles_ref();

			for (const auto& t_pair : tc)
			{
				if (t_pair.second != nullptr && t_pair.second->get_tile_super_type() == tst)
				{
					cnt++;

					if (cnt >= MIN_TERRAIN_COUNT_THRESHOLD)
					{
						matches = true;
						break;
					}
				}
			}
		}
	}

	return matches;
}

#ifdef UNIT_TESTS
#include "unit_tests/EffectTypeTerrainChecker_test.cpp"
#endif