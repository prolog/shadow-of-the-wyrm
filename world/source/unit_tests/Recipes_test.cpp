#include "gtest/gtest.h"

TEST(SW_World_Recipes, serialization_id)
{
	Recipes r;
	EXPECT_EQ(ClassIdentifier::CLASS_ID_RECIPES, r.get_class_identifier());
}

TEST(SW_World_Recipes, saveload)
{
	vector<SkillType> skill_types = { SkillType::SKILL_GENERAL_BREWING, SkillType::SKILL_GENERAL_SMITHING };
	vector<int> skill_required = { 30, 40, 50 };

	string r_id = "r_id";
	Ingredients ingr = { {"ingr1", 1}, {"ingr2", 3} };
	string item_id = "produced_item";

	string r2_id = "r2_id";
	Ingredients ingr2 = { {"ingr3", 5}, {"ingr4", 4} };
	string item2_id = "produced_item2";

	RecipeType recipes_t;

	for (const SkillType st : skill_types)
	{
		for (const int sr : skill_required)
		{
			Recipe r1(r_id, ingr, st, sr, item_id);
			Recipe r2(r2_id, ingr2, st, sr, item2_id);

			recipes_t[st][sr][r_id] = r1;
			recipes_t[st][sr][r2_id] = r2;
		}
	}

	Recipes r(recipes_t);
	Recipes r2;

	EXPECT_FALSE(r == r2);

	ostringstream ss;
	r.serialize(ss);

	istringstream iss(ss.str());
	r2.deserialize(iss);

	EXPECT_TRUE(r == r2);
}
