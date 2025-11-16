#include "gtest/gtest.h"

TEST(SW_World_Recipe, getters)
{
	string r_id = "r_id";
	Ingredients ingr = { {"ingr1", 1}, {"ingr2", 3} };
	uint skill_required = 30;
	string item_id = "produced_item";

	Recipe r(r_id, ingr, SkillType::SKILL_GENERAL_BREWING, skill_required, item_id);

	EXPECT_EQ(ingr, r.get_ingredients());
	EXPECT_EQ(skill_required, r.get_skill_required());
	EXPECT_EQ(item_id, r.get_item_id());
}

TEST(SW_World_Recipe, serialization_id)
{
	Recipe r;
	EXPECT_EQ(ClassIdentifier::CLASS_ID_RECIPE, r.get_class_identifier());
}

TEST(SW_World_Recipe, saveload)
{
	string r_id = "r_id";
	Ingredients ingr = { {"ingr1", 1}, {"ingr2", 3} };
	uint skill_required = 30;
	string item_id = "produced_item";

	Recipe r(r_id, ingr, SkillType::SKILL_GENERAL_SMITHING, skill_required, item_id);
	
	ostringstream oss;
	r.serialize(oss);
	istringstream iss(oss.str());
	
	Recipe r2;
	r2.deserialize(iss);

	EXPECT_TRUE(r == r2);
}

