#pragma once
#include "INPCEffectDecider.hpp"
#include "EffectTypes.hpp"
#include "SpellTypes.hpp"

class NPCEffectDeciderFactory
{
	public:
		static INPCEffectDeciderPtr create_effect_decider(CreaturePtr caster, MapPtr view_map, const EffectType et, const SpellShapeType sst, const bool threats_exist);

	protected:
		NPCEffectDeciderFactory();
		~NPCEffectDeciderFactory();
};
