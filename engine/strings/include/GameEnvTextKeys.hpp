#include <string>

// Used for messages about the game that are not actually related to the game
// content - scripts reloaded, mail for the user, etc.
class GameEnvTextKeys
{
  public:
    static const std::string GAME_ENV_LUA_STATE_CLEARED;
    static std::string get_lua_error(const std::string& lua_error_msg);

  protected:
    static const std::string GAME_ENV_LUA_ERROR;

    GameEnvTextKeys();
    ~GameEnvTextKeys();
};