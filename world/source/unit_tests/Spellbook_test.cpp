#include "gtest/gtest.h"

TEST(SL_World_Spellbook, serialization_id)
{
  Spellbook book;

  EXPECT_EQ(CLASS_ID_SPELLBOOK, book.get_class_identifier());
}

TEST(SL_World_Spellbook, saveload)
{
  Spellbook book, book2;

  book.set_unidentified_description_sid("serialize_break_test!");
  book.set_spell_id("big_spell");

  ostringstream ss;

  book.serialize(ss);

  istringstream iss(ss.str());

  book2.deserialize(iss);

  EXPECT_TRUE(book == book2);
}
