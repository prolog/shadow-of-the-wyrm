#include "gtest/gtest.h"

TEST(SL_World_Book, serialization_id)
{
  Book book;

  EXPECT_EQ(CLASS_ID_BOOK, book.get_class_identifier());
}
