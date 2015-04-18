#include "CommandKeys.hpp"

using namespace std;

CommandKeys::CommandKeys()
{
}

CommandKeys::~CommandKeys()
{
}

// Initialize the command keys
const string CommandKeys::QUIT           = "QUIT";
const string CommandKeys::VERSION        = "VERSION";
const string CommandKeys::GAME_DATE_TIME = "GAME_DATE_TIME";
const string CommandKeys::MOVE_NORTHWEST = "MOVE_NORTHWEST";
const string CommandKeys::MOVE_NORTH     = "MOVE_NORTH";
const string CommandKeys::MOVE_NORTHEAST = "MOVE_NORTHEAST";
const string CommandKeys::MOVE_WEST      = "MOVE_WEST";
const string CommandKeys::SEARCH         = "SEARCH";
const string CommandKeys::MOVE_EAST      = "MOVE_EAST";
const string CommandKeys::MOVE_SOUTHWEST = "MOVE_SOUTHWEST";
const string CommandKeys::MOVE_SOUTH     = "MOVE_SOUTH";
const string CommandKeys::MOVE_SOUTHEAST = "MOVE_SOUTHEAST";
const string CommandKeys::MOVE_UP        = "MOVE_UP";
const string CommandKeys::MOVE_DOWN      = "MOVE_DOWN";
const string CommandKeys::AUTOMATIC_MOVEMENT = "AUTOMATIC_MOVEMENT";
const string CommandKeys::PICK_UP_ITEM   = "PICK_UP_ITEM";
const string CommandKeys::DROP_ITEM      = "DROP_ITEM";
const string CommandKeys::CHAR_DUMP      = "CHAR_DUMP";
const string CommandKeys::INVENTORY      = "INVENTORY";
const string CommandKeys::PRAY           = "PRAY";
const string CommandKeys::MELEE_WEAPON_INFO = "MELEE_WEAPON_INFO";
const string CommandKeys::RANGED_WEAPON_INFO = "RANGED_WEAPON_INFO";
const string CommandKeys::SELECT_TILE    = "SELECT_TILE";
const string CommandKeys::FIRE_MISSILE   = "FIRE_MISSILE";
const string CommandKeys::QUAFF          = "QUAFF";
const string CommandKeys::READ           = "READ";
const string CommandKeys::CHECK_CURRENCY = "CHECK_CURRENCY";
const string CommandKeys::SAVE_GAME      = "SAVE_GAME";
const string CommandKeys::EAT            = "EAT";
const string CommandKeys::CHAT           = "CHAT";
const string CommandKeys::APPLY_FEATURE  = "APPLY_FEATURE";
const string CommandKeys::QUEST_LIST     = "QUEST_LIST";
const string CommandKeys::RELOAD_SCRIPTS_AND_SIDS = "RELOAD_SCRIPTS_AND_SIDS";
const string CommandKeys::RUN_SCRIPT     = "RUN_SCRIPT";
const string CommandKeys::CAST_SPELL     = "CAST_SPELL";
const string CommandKeys::BESTIARY       = "BESTIARY";
const string CommandKeys::EVOKE          = "EVOKE";
const string CommandKeys::SHOW_RESISTANCES = "SHOW_RESISTANCES";
const string CommandKeys::SHOW_CONDUCTS  = "SHOW_CONDUCTS";
const string CommandKeys::LATEST_MESSAGES = "LATEST_MESSAGES";
const string CommandKeys::KICK           = "KICK";
const string CommandKeys::OFFER          = "OFFER";
const string CommandKeys::SKIN           = "SKIN";
const string CommandKeys::PIETY          = "PIETY";
const string CommandKeys::EXPERIENCE     = "EXPERIENCE";
const string CommandKeys::CUSTOM_SCRIPT_COMMAND = "CUSTOM_SCRIPT_COMMAND";

const string CommandKeys::ATTACK_NORTHWEST = "ATTACK_NORTHWEST";
const string CommandKeys::ATTACK_NORTH     = "ATTACK_NORTH";
const string CommandKeys::ATTACK_NORTHEAST = "ATTACK_NORTHEAST";
const string CommandKeys::ATTACK_WEST      = "ATTACK_WEST";
const string CommandKeys::ATTACK_EAST      = "ATTACK_EAST";
const string CommandKeys::ATTACK_SOUTHWEST = "ATTACK_SOUTHWEST";
const string CommandKeys::ATTACK_SOUTH     = "ATTACK_SOUTH";
const string CommandKeys::ATTACK_SOUTHEAST = "ATTACK_SOUTHEAST";

bool CommandKeys::is_movement_type_key(const string& key)
{
  bool is_movement = false;

  if ((key == CommandKeys::MOVE_NORTHWEST)
   || (key == CommandKeys::MOVE_NORTH)
   || (key == CommandKeys::MOVE_NORTHEAST)
   || (key == CommandKeys::MOVE_WEST)
   || (key == CommandKeys::MOVE_EAST)
   || (key == CommandKeys::MOVE_SOUTHWEST)
   || (key == CommandKeys::MOVE_SOUTH)
   || (key == CommandKeys::MOVE_SOUTHEAST))
  {
    is_movement = true;
  }

  return is_movement;
}

bool CommandKeys::is_attack_type_key(const string& key)
{
  bool is_attack = false;

  if ((key == CommandKeys::ATTACK_NORTHWEST)
   || (key == CommandKeys::ATTACK_NORTH)
   || (key == CommandKeys::ATTACK_NORTHEAST)
   || (key == CommandKeys::ATTACK_WEST)
   || (key == CommandKeys::ATTACK_EAST)
   || (key == CommandKeys::ATTACK_SOUTHWEST)
   || (key == CommandKeys::ATTACK_SOUTH)
   || (key == CommandKeys::ATTACK_SOUTHEAST))
  {
    is_attack = true;
  }

  return is_attack;
}
