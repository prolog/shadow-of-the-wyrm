#include "gtest/gtest.h"

TEST(SW_World_Ingredient, serialization_id)
{
	Ingredient i;

	EXPECT_EQ(ClassIdentifier::CLASS_ID_INGREDIENT, i.get_class_identifier());
}

TEST(SW_World_Ingredient, saveload)
{
	Ingredient i("", "abc", 123);
	Ingredient i2;

	ostringstream ss;
	i.serialize(ss);

	istringstream iss(ss.str());
	i2.deserialize(iss);

	EXPECT_TRUE(i == i2);
}