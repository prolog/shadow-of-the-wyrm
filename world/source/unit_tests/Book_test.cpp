#include "gtest/gtest.h"

TEST(SL_World_Book, serialization_id)
{
  Book book;

  EXPECT_EQ(CLASS_ID_BOOK, book.get_class_identifier());
}

TEST(SL_World_Book, saveload)
{
  Book book, book2;

  book.set_unidentified_description_sid("serialize_break_test!");

  ostringstream ss;

  book.serialize(ss);

  istringstream iss(ss.str());

  book2.deserialize(iss);

  EXPECT_TRUE(book == book2);
}
