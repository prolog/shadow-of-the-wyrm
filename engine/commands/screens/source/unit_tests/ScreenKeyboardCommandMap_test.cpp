#include "gtest/gtest.h"

TEST(SL_Engine_Commands_Screens_ScreenKeyboardCommandMap, serialization_id)
{
  ScreenKeyboardCommandMap skcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SCREEN_KEYBOARD_COMMAND_MAP, skcm.get_class_identifier());
}

class SL_Engine_Commands_Screens_ScreenKeyboardCommandMapFixture : public SL_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    ScreenKeyboardCommandMap skcm;
};

void SL_Engine_Commands_Screens_ScreenKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(skcm);
}

TEST_F(SL_Engine_Commands_Screens_ScreenKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  skcm.serialize(ss);

  istringstream iss(ss.str());

  ScreenKeyboardCommandMap skcm2;

  skcm2.deserialize(iss);

  EXPECT_TRUE(skcm == skcm2);
}

