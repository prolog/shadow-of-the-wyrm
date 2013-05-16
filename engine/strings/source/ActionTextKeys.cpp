#include <boost/algorithm/string/replace.hpp>
#include "ActionTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ActionTextKeys::ActionTextKeys()
{
}

ActionTextKeys::~ActionTextKeys()
{
}

string ActionTextKeys::get_general_action_message(const string& desc_sid, const string& item_desc_sid, const string& player_sid, const string& monster_sid, const bool is_player)
{
  string message = StringTable::get(player_sid);
  
  if (!is_player)
  {
    message = StringTable::get(monster_sid);
    // Replace the creature part
    boost::replace_first(message, "%s", StringTable::get(desc_sid));
    message[0] = toupper(message[0]);
  }
  
  // Replace the item part.
  boost::replace_first(message, "%s", StringTable::get(item_desc_sid));
  
  return message;
}

string ActionTextKeys::get_evoke_message(const string& desc_sid, const string& wand_desc_sid, const bool is_player)
{
  return get_general_action_message(desc_sid, wand_desc_sid, ACTION_EVOKE_PLAYER, ACTION_EVOKE_MONSTER, is_player);
}

string ActionTextKeys::get_quaff_message(const string& desc_sid, const string& potion_desc_sid, const bool is_player)
{
  return get_general_action_message(desc_sid, potion_desc_sid, ACTION_QUAFF_PLAYER, ACTION_QUAFF_MONSTER, is_player);
}

string ActionTextKeys::get_read_message(const string& desc_sid, const string& readable_desc_sid, const bool is_player)
{
  return get_general_action_message(desc_sid, readable_desc_sid, ACTION_READ_PLAYER, ACTION_READ_MONSTER, is_player);
}

string ActionTextKeys::get_eat_message(const string& desc_sid, const string& consumable_desc_sid, const bool is_player)
{
  return get_general_action_message(desc_sid, consumable_desc_sid, ACTION_EAT_PLAYER, ACTION_EAT_MONSTER, is_player);
}

string ActionTextKeys::get_full_message(const string& desc_sid, const string& consumable_desc_sid, const bool is_player)
{
  return get_general_action_message(desc_sid, consumable_desc_sid, ACTION_FULL_PLAYER, ACTION_FULL_MONSTER, is_player);
}

string ActionTextKeys::get_spellcasting_message(const Spell& spell, const string& creature_desc_sid, const bool is_player)
{
  string spellcasting_message;

  if (is_player)
  {
    spellcasting_message = StringTable::get(spell.get_player_cast_message_sid());
  }
  else
  {
    spellcasting_message = StringTable::get(spell.get_monster_cast_message_sid());
    boost::replace_first(spellcasting_message, "%s", StringTable::get(creature_desc_sid));
  }

  return spellcasting_message;
}

string ActionTextKeys::get_spellcasting_cancelled_message(const string& creature_desc_sid, const bool is_player)
{
  string cancelled_msg;
  
  if (is_player)
  {
    cancelled_msg = StringTable::get(ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_PLAYER);
  }
  else
  {
    cancelled_msg = StringTable::get(ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_MONSTER);
    boost::replace_first(cancelled_msg, "%s", StringTable::get(creature_desc_sid));
  }

  return cancelled_msg;
}

string ActionTextKeys::get_bestiary_search_message(const string& previous_search_text)
{
  string search_msg = StringTable::get(ActionTextKeys::ACTION_BESTIARY_WHICH_CREATURE);

  if (!previous_search_text.empty())
  {
    search_msg = StringTable::get(ActionTextKeys::ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE);
    boost::replace_first(search_msg, "%s", previous_search_text);
  }

  return search_msg;
}

const string ActionTextKeys::ACTION_NOT_FOUND                  = "ACTION_NOT_FOUND";
const string ActionTextKeys::ACTION_SEARCH                     = "ACTION_SEARCH";
const string ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED        = "ACTION_PICK_UP_NOT_ALLOWED";
const string ActionTextKeys::ACTION_DROP_NOT_ALLOWED           = "ACTION_DROP_NOT_ALLOWED";
const string ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED      = "ACTION_DROP_NO_ITEM_SELECTED";
const string ActionTextKeys::ACTION_DROP_QUANTITY_PROMPT       = "ACTION_DROP_QUANTITY_PROMPT";
const string ActionTextKeys::ACTION_DROP_INVALID_QUANTITY      = "ACTION_DROP_INVALID_QUANTITY";
const string ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND  = "ACTION_PICK_UP_NOTHING_ON_GROUND";
const string ActionTextKeys::ACTION_MOVEMENT_BLOCKED           = "ACTION_MOVEMENT_BLOCKED";
const string ActionTextKeys::ACTION_PLAYER_DROWNING            = "ACTION_PLAYER_DROWNING";
const string ActionTextKeys::ACTION_PLAYER_FALL_FROM_MOUNTAIN  = "ACTION_PLAYER_FALL_FROM_MOUNTAIN";
const string ActionTextKeys::ACTION_PLAYER_STARVING_TO_DEATH   = "ACTION_PLAYER_STARVING_TO_DEATH";
const string ActionTextKeys::ACTION_DETECTED_HOSTILE_CREATURES = "ACTION_DETECTED_HOSTILE_CREATURES";
const string ActionTextKeys::ACTION_LOOK                       = "ACTION_LOOK";
const string ActionTextKeys::ACTION_LOOK_UNEXPLORED_TILE       = "ACTION_LOOK_UNEXPLORED_TILE";
const string ActionTextKeys::ACTION_LOOK_TILE_OUT_OF_RANGE     = "ACTION_LOOK_TILE_OUT_OF_RANGE";
const string ActionTextKeys::ACTION_FIRE                       = "ACTION_FIRE";
const string ActionTextKeys::ACTION_NOTHING_HAPPENS            = "ACTION_NOTHING_HAPPENS";
const string ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY         = "ACTION_CHAT_NOBODY_NEARBY";
const string ActionTextKeys::ACTION_CHAT_NO_RESPONSE           = "ACTION_CHAT_NO_RESPONSE";
const string ActionTextKeys::ACTION_GET_DIRECTION              = "ACTION_GET_DIRECTION";
const string ActionTextKeys::ACTION_GET_CARDINAL_DIRECTION     = "ACTION_GET_CARDINAL_DIRECTION";
const string ActionTextKeys::ACTION_OPEN_DOOR                  = "ACTION_OPEN_DOOR";
const string ActionTextKeys::ACTION_CLOSE_DOOR                 = "ACTION_CLOSE_DOOR";
const string ActionTextKeys::ACTION_DOOR_DESTROYED             = "ACTION_DOOR_DESTROYED";
const string ActionTextKeys::ACTION_APPLY_NO_FEATURES_PRESENT  = "ACTION_APPLY_NO_FEATURES_PRESENT";
const string ActionTextKeys::ACTION_HANDLE_LOCK                = "ACTION_HANDLE_LOCK";
const string ActionTextKeys::ACTION_HANDLE_LOCK_NO_KEY         = "ACTION_HANDLE_LOCK_NO_KEY";
const string ActionTextKeys::ACTION_BESTIARY_WHICH_CREATURE    = "ACTION_BESTIARY_WHICH_CREATURE";
const string ActionTextKeys::ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS = "ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS";

const string ActionTextKeys::ACTION_EVOKE_PLAYER               = "ACTION_EVOKE_PLAYER";
const string ActionTextKeys::ACTION_EVOKE_MONSTER              = "ACTION_EVOKE_MONSTER";
const string ActionTextKeys::ACTION_QUAFF_PLAYER               = "ACTION_QUAFF_PLAYER";
const string ActionTextKeys::ACTION_QUAFF_MONSTER              = "ACTION_QUAFF_MONSTER";
const string ActionTextKeys::ACTION_READ_PLAYER                = "ACTION_READ_PLAYER";
const string ActionTextKeys::ACTION_READ_MONSTER               = "ACTION_READ_MONSTER";
const string ActionTextKeys::ACTION_EAT_PLAYER                 = "ACTION_EAT_PLAYER";
const string ActionTextKeys::ACTION_EAT_MONSTER                = "ACTION_EAT_MONSTER";
const string ActionTextKeys::ACTION_FULL_PLAYER                = "ACTION_FULL_PLAYER";
const string ActionTextKeys::ACTION_FULL_MONSTER               = "ACTION_FULL_MONSTER";
const string ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_PLAYER = "ACTION_SPELLCASTING_CANCELLED_PLAYER";
const string ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_MONSTER = "ACTION_SPELLCASTING_CANCELLED_MONSTER";
const string ActionTextKeys::ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE = "ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE";
const string ActionTextKeys::ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION = "ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION";
