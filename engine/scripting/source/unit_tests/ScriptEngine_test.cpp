#include "gtest/gtest.h"

TEST(SL_Engine_Scripting_ScriptEngine, serialization_id)
{
  ScriptEngine se;

  EXPECT_EQ(CLASS_ID_SCRIPT_ENGINE, se.get_class_identifier());
}

TEST(SL_engine_Scripting_ScriptEngine, saveload)
{
  ScriptEngine se, se2;

  se.set_last_executed("some_lua_command");

  ostringstream ss;

  se.serialize(ss);

  istringstream iss(ss.str());

  se2.deserialize(iss);

  EXPECT_TRUE(se == se2);
}

