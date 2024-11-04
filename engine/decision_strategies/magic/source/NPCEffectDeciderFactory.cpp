#include "NPCEffectDeciderFactory.hpp"
#include "NPCEffectDeciders.hpp"

NPCEffectDeciderFactory::NPCEffectDeciderFactory()
{
}

NPCEffectDeciderFactory::~NPCEffectDeciderFactory()
{
}

INPCEffectDeciderPtr NPCEffectDeciderFactory::create_effect_decider(CreaturePtr caster, MapPtr view_map, const EffectType et, const SpellShapeType sst, const bool threats_exist)
{
	INPCEffectDeciderPtr decider;
	
	if (et == EffectType::EFFECT_TYPE_WATER_BREATHING)
	{
		decider = std::make_unique<TerrainNPCEffectDecider>(caster, view_map, et);
	}
	else if (et == EffectType::EFFECT_TYPE_FLYING)
	{
		decider = std::make_unique<TerrainNPCEffectDecider>(caster, view_map, et);
	}
	else if (et == EffectType::EFFECT_TYPE_MODIFY_STATISTICS)
	{
		decider = std::make_unique<ModifyStatisticsNPCEffectDecider>(caster, view_map, sst, threats_exist);
	}
	else
	{
		decider = std::make_unique<DefaultNPCEffectDecider>();
	}

	return decider;
}
