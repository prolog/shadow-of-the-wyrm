#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Menus_MenuKeyboardCommandMap, serialization_id)
{
  MenuKeyboardCommandMap mkcm;

  EXPECT_EQ(CLASS_ID_MENU_KEYBOARD_COMMAND_MAP, mkcm.get_class_identifier());
}

class SL_Engine_Commands_Menus_MenuKeyboardCommandMapFixture : public SL_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    MenuKeyboardCommandMap mkcm;
};

void SL_Engine_Commands_Menus_MenuKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(mkcm);
}

TEST_F(SL_Engine_Commands_Menus_MenuKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  mkcm.serialize(ss);

  istringstream iss(ss.str());

  MenuKeyboardCommandMap mkcm2;

  mkcm2.deserialize(iss);

  EXPECT_TRUE(mkcm == mkcm2);
}

