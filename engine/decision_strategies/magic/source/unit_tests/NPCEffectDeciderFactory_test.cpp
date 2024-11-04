#include "gtest/gtest.h"

TEST(SW_Engine_DecisionStrategies_Magic_NPCEffectDeciderFactory, all_effects_produce_non_null_pointer)
{
	for (int i = 0; i < static_cast<int>(EffectType::EFFECT_TYPE_LAST); i++)
	{
		EffectType et = static_cast<EffectType>(i);
		INPCEffectDeciderPtr ed = NPCEffectDeciderFactory::create_effect_decider(nullptr, nullptr, et, SpellShapeType::SPELL_SHAPE_TARGET_SELF, true);
		
		EXPECT_TRUE(ed != nullptr);
	}
}
