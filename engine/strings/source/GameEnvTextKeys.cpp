#include <boost/algorithm/string/replace.hpp>
#include "GameEnvTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Game Environment text keys:
GameEnvTextKeys::GameEnvTextKeys()
{
}

GameEnvTextKeys::~GameEnvTextKeys()
{
}

const string GameEnvTextKeys::GAME_ENV_LUA_STATE_CLEARED = "GAME_ENV_LUA_STATE_CLEARED";
const string GameEnvTextKeys::GAME_ENV_LUA_ERROR = "GAME_ENV_LUA_ERROR";

string GameEnvTextKeys::get_lua_error(const string& lua_error_msg)
{
  string error_msg = StringTable::get(GAME_ENV_LUA_ERROR);
  boost::replace_first(error_msg, "%s", lua_error_msg);

  return error_msg;
}