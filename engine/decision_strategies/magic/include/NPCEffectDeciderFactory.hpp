#pragma once
#include "INPCEffectDecider.hpp"
#include "Creature.hpp"
#include "EffectTypes.hpp"
#include "Map.hpp"
#include "SpellTypes.hpp"

class NPCEffectDeciderFactory
{
	public:
		static INPCEffectDeciderPtr create_effect_decider(CreaturePtr caster, MapPtr view_map, MapPtr current_game_game, const EffectType et, const SpellShapeType sst, const bool threats_exist);

	protected:
		NPCEffectDeciderFactory();
		~NPCEffectDeciderFactory();
};
