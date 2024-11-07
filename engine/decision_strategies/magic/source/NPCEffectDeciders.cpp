#include "global_prototypes.hpp"
#include "NPCEffectDeciders.hpp"
#include "Conversion.hpp"
#include "EffectTypeTerrainChecker.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"

using std::string;

// DefaultNPCEffectDecider
DefaultNPCEffectDecider::DefaultNPCEffectDecider()
{
}

DefaultNPCEffectDecider::DefaultNPCEffectDecider(CreaturePtr new_caster, MapPtr new_map)
: caster(new_caster), view_map(new_map)
{
}

DefaultNPCEffectDecider::~DefaultNPCEffectDecider()
{
}

bool DefaultNPCEffectDecider::decide() const
{
	return false;
}

// TerrainNPCEffectDecider
TerrainNPCEffectDecider::TerrainNPCEffectDecider(CreaturePtr new_caster, MapPtr new_map, const EffectType new_et)
: DefaultNPCEffectDecider(new_caster, new_map), et(new_et)
{
}

TerrainNPCEffectDecider::~TerrainNPCEffectDecider()
{
}

bool TerrainNPCEffectDecider::decide() const
{
	if (caster != nullptr && view_map != nullptr)
	{
		EffectTypeTerrainChecker ettc;
		return ettc.does_effect_match_terrain(caster, view_map, et);
	}

	return DefaultNPCEffectDecider::decide();
}

// ModifyStatisticsNPCEffectDecider
ModifyStatisticsNPCEffectDecider::ModifyStatisticsNPCEffectDecider(CreaturePtr new_caster, MapPtr new_map, const SpellShapeType new_sst, const bool new_threats_exist)
: DefaultNPCEffectDecider(new_caster, new_map), sst(new_sst), threats_exist(new_threats_exist)
{
}

ModifyStatisticsNPCEffectDecider::~ModifyStatisticsNPCEffectDecider()
{
}

bool ModifyStatisticsNPCEffectDecider::decide() const
{
	if (sst == SpellShapeType::SPELL_SHAPE_TARGET_SELF)
	{
		return threats_exist;
	}

	// Modify later if need be, but for now, NPCs only cast self-targetting
	// modify statistics spells.
	return false;
}

// CleansingNPCEffectDecider
CleansingNPCEffectDecider::CleansingNPCEffectDecider(CreaturePtr new_caster, MapPtr new_map)
: DefaultNPCEffectDecider(new_caster, new_map)
{
}

CleansingNPCEffectDecider::~CleansingNPCEffectDecider()
{
}

bool CleansingNPCEffectDecider::decide() const
{
	bool dec = true;
	Game& game = Game::instance();
	MapPtr current_map = game.get_current_map();

	if (current_map != nullptr)
	{
		string regen_rate = current_map->get_property(MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE);

		if (!regen_rate.empty())
		{
			float rr = String::to_float(regen_rate);

			if (fequal(rr, 0.0f))
			{
				dec = false;
			}
		}
	}

	return dec;
}

#ifdef UNIT_TESTS
#include "unit_tests/NPCEffectDeciders_test.cpp"
#endif