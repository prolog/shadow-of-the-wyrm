#include "gtest/gtest.h"

class SL_Engine_Strings_StringTable : public ::testing::Test
{
  public:
    bool is_external_file(const string& str);
    string parse_file_name(const string& str);

  protected:
    void SetUp();
};

bool SL_Engine_Strings_StringTable::is_external_file(const string& value)
{
  return StringTable::is_external_file(value);
}

string SL_Engine_Strings_StringTable::parse_file_name(const string& value)
{
  return StringTable::parse_file_name(value);
}

void SL_Engine_Strings_StringTable::SetUp()
{
}

TEST_F(SL_Engine_Strings_StringTable, check_is_external_file)
{
  string file_ref = "   [[fdsafdsa]] ";
  string not_file_ref = "[Some In-Game Prompt]";

  EXPECT_TRUE(is_external_file(file_ref));
  EXPECT_FALSE(is_external_file(not_file_ref));
}

TEST_F(SL_Engine_Strings_StringTable, check_parse_file_name)
{
  string not_file_ref = "fdsafdsa";

  EXPECT_EQ("fdsafdsa", parse_file_name(not_file_ref));

  string file_ref = "[[dir/file.txt]]";

  EXPECT_EQ("dir/file.txt", parse_file_name(file_ref));
}

