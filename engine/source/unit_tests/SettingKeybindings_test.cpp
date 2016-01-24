#include "gtest/gtest.h"

TEST(SW_Engine_SettingKeybindings, empty_setting)
{
  string setting = "";

  SettingKeybindings sk;
  vector<string> bindings = sk.get_keybindings(setting);

  EXPECT_EQ(0, bindings.size());
}

TEST(SW_Engine_SettingKeybindings, parse_single)
{
  string setting = "123";

  SettingKeybindings sk;
  vector<string> bindings = sk.get_keybindings(setting);

  EXPECT_EQ(1, bindings.size());
  EXPECT_EQ("123", bindings.at(0));
}

TEST(SW_Engine_SettingKeybindings, parse_multiple)
{
  string setting = "123|343|1222";

  SettingKeybindings sk;
  vector<string> bindings = sk.get_keybindings(setting);

  EXPECT_EQ(3, bindings.size());
  EXPECT_EQ("123", bindings.at(0));
  EXPECT_EQ("343", bindings.at(1));
  EXPECT_EQ("1222", bindings.at(2));
}

