#pragma once
#include "INPCEffectDecider.hpp"
#include "Map.hpp"
#include "SpellTypes.hpp"

// NPC Effect Deciders determine if NPCs will use a certain effect. These
// are separated out so that they can be used both for spell and item
// effects.

// Default - always returns false.
class DefaultNPCEffectDecider : public INPCEffectDecider
{
	public:
		DefaultNPCEffectDecider();
		DefaultNPCEffectDecider(CreaturePtr new_caster, MapPtr new_view_map);
		~DefaultNPCEffectDecider();

		bool decide() const override;

	protected:
		CreaturePtr caster;
		MapPtr view_map;
};

// Used for water breathing, flying, etc.
class TerrainNPCEffectDecider : public DefaultNPCEffectDecider
{
	public:
		TerrainNPCEffectDecider(CreaturePtr new_caster, MapPtr new_view_map, const EffectType new_et);
		~TerrainNPCEffectDecider();

		bool decide() const override;

	protected:
		EffectType et;
};

// Modify Statistics
class ModifyStatisticsNPCEffectDecider : public DefaultNPCEffectDecider
{
	public:
		ModifyStatisticsNPCEffectDecider(CreaturePtr new_caster, MapPtr new_view_map, const SpellShapeType new_sst, const bool new_threats_exist);
		~ModifyStatisticsNPCEffectDecider();

		bool decide() const override;

	protected:
		SpellShapeType sst;
		bool threats_exist;
};
