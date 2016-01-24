#include "gtest/gtest.h"

TEST(SW_Engine_Commands_Magic_MagicKeyboardCommandMap, serialization_id)
{
  MagicKeyboardCommandMap mkcm;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAGIC_KEYBOARD_COMMAND_MAP, mkcm.get_class_identifier());
}

class SW_Engine_Commands_Magic_MagicKeyboardCommandMapFixture : public SW_Engine_Commands_KeyboardCommandMapFixture
{
  public:
    void SetUp();

  protected:
    MagicKeyboardCommandMap mkcm;
};

void SW_Engine_Commands_Magic_MagicKeyboardCommandMapFixture::SetUp()
{
  initialize_kcm_for_unit_tests(mkcm);
}

TEST_F(SW_Engine_Commands_Magic_MagicKeyboardCommandMapFixture, saveload)
{
  ostringstream ss;

  mkcm.serialize(ss);

  istringstream iss(ss.str());

  MagicKeyboardCommandMap mkcm2;

  mkcm2.deserialize(iss);

  EXPECT_TRUE(mkcm == mkcm2);
}
