#include <boost/algorithm/string/replace.hpp>
#include "ActionTextKeys.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

ActionTextKeys::ActionTextKeys()
{
}

ActionTextKeys::~ActionTextKeys()
{
}

string ActionTextKeys::get_general_message(const string& desc_sid, const string& player_message_sid, const string& monster_message_sid, const bool is_player)
{
  string message = StringTable::get(player_message_sid);

  if (!is_player)
  {
    message = StringTable::get(monster_message_sid);

    // Replace the creature part
    boost::replace_first(message, "%s", StringTable::get(desc_sid));
    message[0] = toupper(message[0]);
  }

  return message;
}

string ActionTextKeys::get_general_action_message(const string& desc_sid, const string& item_desc, const string& player_sid, const string& monster_sid, const bool is_player)
{
  string message = get_general_message(desc_sid, player_sid, monster_sid, is_player);
  
  // Replace the item part.
  boost::replace_first(message, "%s", item_desc);
  
  return message;
}

string ActionTextKeys::get_evoke_message(const string& desc_sid, const string& wand_desc, const bool is_player)
{
  return get_general_action_message(desc_sid, wand_desc, ACTION_EVOKE_PLAYER, ACTION_EVOKE_MONSTER, is_player);
}

string ActionTextKeys::get_quaff_message(const string& desc_sid, const string& potion_desc, const bool is_player)
{
  return get_general_action_message(desc_sid, potion_desc, ACTION_QUAFF_PLAYER, ACTION_QUAFF_MONSTER, is_player);
}

string ActionTextKeys::get_read_message(const string& player_read_message, const string& monster_read_message, const string& desc_sid, const string& readable_desc, const bool is_player)
{
  return get_general_action_message(desc_sid, readable_desc, player_read_message, monster_read_message, is_player);
}

string ActionTextKeys::get_eat_message(const string& desc_sid, const string& consumable_desc, const bool is_player)
{
  return get_general_action_message(desc_sid, consumable_desc, ACTION_EAT_PLAYER, ACTION_EAT_MONSTER, is_player);
}

string ActionTextKeys::get_eat_confirmation_message(const string& consumable_desc)
{
  string message = StringTable::get(ACTION_EAT_CONFIRMATION);
  boost::replace_first(message, "%s", consumable_desc);

  return message;
}

string ActionTextKeys::get_full_message(const string& desc_sid, const string& consumable_desc, const bool is_player)
{
  return get_general_action_message(desc_sid, consumable_desc, ACTION_FULL_PLAYER, ACTION_FULL_MONSTER, is_player);
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

  spellcasting_message[0] = toupper(spellcasting_message[0]);
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

string ActionTextKeys::get_pour_message(const string& creature_desc_sid, const string& item_desc_sid, const bool is_player)
{
  string pour_msg;

  if (is_player)
  {
    pour_msg = StringTable::get(ActionTextKeys::ACTION_POUR_PLAYER);
  }
  else
  {
    pour_msg = StringTable::get(ActionTextKeys::ACTION_POUR_MONSTER);
    boost::replace_first(pour_msg, "%s", StringTable::get(creature_desc_sid));
  }

  boost::replace_first(pour_msg, "%s", StringTable::get(item_desc_sid));

  return pour_msg;
}

string ActionTextKeys::get_stumble_message(const string& creature_desc_sid, const bool is_player)
{
  string stumble_msg;

  if (is_player)
  {
    stumble_msg = StringTable::get(ActionTextKeys::ACTION_STUMBLE_PLAYER);
  }
  else
  {
    stumble_msg = StringTable::get(ActionTextKeys::ACTION_STUMBLE_MONSTER);
    boost::replace_first(stumble_msg, "%s", StringTable::get(creature_desc_sid));
  }

  return stumble_msg;
}

string ActionTextKeys::get_alcohol_poisoning_death_message(const string& creature_desc_sid, const bool is_player)
{
  return get_general_message(creature_desc_sid, ActionTextKeys::ACTION_ALCOHOL_POISONING_PLAYER, ActionTextKeys::ACTION_ALCOHOL_POISONING_MONSTER, is_player);
}

string ActionTextKeys::get_kick_message(const string& desc_sid, const bool is_player)
{
  return get_general_message(desc_sid, ACTION_KICK_PLAYER, ACTION_KICK_MONSTER, is_player);
}

string ActionTextKeys::get_kick_object_message(const string& desc_sid, const string& object_desc, const bool is_player)
{
  string kick_msg;

  if (is_player)
  {
    kick_msg = StringTable::get(ACTION_KICK_OBJECT_PLAYER);
    boost::replace_first(kick_msg, "%s", object_desc);
  }
  else
  {
    kick_msg = StringTable::get(ACTION_KICK_OBJECT_MONSTER);
    boost::replace_first(kick_msg, "%s1", desc_sid);
    boost::replace_first(kick_msg, "%s2", object_desc);
  }

  return kick_msg;
}

string ActionTextKeys::get_knock_back_message(const string& defend_desc_sid, const bool defend_is_player)
{
  string kb_msg;

  if (defend_is_player)
  {
    kb_msg = StringTable::get(ACTION_KNOCK_BACK_PLAYER);
  }
  else
  {
    kb_msg = StringTable::get(ACTION_KNOCK_BACK_MONSTER);
    boost::replace_first(kb_msg, "%s", StringTable::get(defend_desc_sid));
    kb_msg[0] = toupper(kb_msg[0]);
  }

  return kb_msg;
}

string ActionTextKeys::get_generic_wear_off_message(const string& desc_sid)
{
  string msg;

  msg = StringTable::get(ACTION_SPELL_WEAR_OFF_MONSTER);
  boost::replace_first(msg, "%s", desc_sid);

  return msg;
}

string ActionTextKeys::get_item_breakage_message(const string& creature_desc_sid, const bool is_player, const string& item_desc)
{
  string msg = StringTable::get(ACTION_ITEM_BREAKAGE_PLAYER);

  if (!is_player)
  {
    msg = StringTable::get(ACTION_ITEM_BREAKAGE_MONSTER);
    boost::replace_first(msg, "%s1", creature_desc_sid);
  }

  boost::replace_first(msg, "%s2", item_desc);

  return msg;
}

string ActionTextKeys::get_spit_out_message(const string& item_usage_desc)
{
  string msg = StringTable::get(ACTION_SPIT_OUT_SEED);
  boost::replace_first(msg, "%s", item_usage_desc);

  return msg;
}

string ActionTextKeys::get_seed_planted_message(const bool blind, const string& item_usage_desc)
{
  string msg = StringTable::get(ACTION_SEED_PLANTED);
  string replace = item_usage_desc;

  if (blind)
  {
    replace = StringTable::get(TextKeys::SOMETHING);
  }

  boost::replace_first(msg, "%s", replace);

  return msg;
}

string ActionTextKeys::get_random_bait_message()
{
  vector<string> bait_msgs = {ACTION_FISHING_BAIT1, ACTION_FISHING_BAIT2, ACTION_FISHING_BAIT3};
  return StringTable::get(bait_msgs.at(RNG::range(0, bait_msgs.size()-1)));
}

string ActionTextKeys::get_fishing_outcome_message(const FishingOutcomeType fot)
{
  string msg_sid;

  switch (fot)
  {
    case FishingOutcomeType::FISHING_OUTCOME_NO_CATCH:
      msg_sid = ACTION_FISHING_NO_CATCH;
      break;
    case FishingOutcomeType::FISHING_OUTCOME_ESCAPE:
      msg_sid = ACTION_FISHING_ESCAPE;
      break;
    case FishingOutcomeType::FISHING_OUTCOME_NIBBLE:
      msg_sid = ACTION_FISHING_NIBBLE;
      break;
    case FishingOutcomeType::FISHING_OUTCOME_CATCH:
      msg_sid = ACTION_FISHING_CATCH;
      break;
    case FishingOutcomeType::FISHING_OUTCOME_UNDEFINED:
    default:
      break;
  }

  string msg = StringTable::get(msg_sid);

  return msg;
}

string ActionTextKeys::get_already_stolen_message(const string& desc)
{
  string msg = StringTable::get(ACTION_THIEVERY_ALREADY_STOLEN);

  boost::replace_first(msg, "%s", desc);
  msg[0] = toupper(msg[0]);

  return msg;
}

string ActionTextKeys::get_no_pockets_message(const string& desc)
{
  string msg = StringTable::get(ACTION_THIEVERY_NO_POCKETS);

  boost::replace_first(msg, "%s", desc);
  msg[0] = toupper(msg[0]);

  return msg;
}

string ActionTextKeys::get_steal_successful_message(const string& creature_desc, const string& item_desc, const bool is_player)
{
  string msg = ACTION_THIEVERY_STEAL_SUCCESSFUL_PLAYER;

  if (!is_player)
  {
    msg = ACTION_THIEVERY_STEAL_SUCCESSFUL_MONSTER;
  }

  msg = StringTable::get(msg);
  boost::replace_first(msg, "%s1", creature_desc);
  boost::replace_first(msg, "%s2", item_desc);
  msg[0] = toupper(msg[0]);

  return msg;
}

string ActionTextKeys::get_steal_unsuccessful_message(const string& stealing_desc, const string& steal_desc, const bool is_player)
{
  string msg = ACTION_THIEVERY_STEAL_UNSUCCESSFUL_PLAYER;

  if (!is_player)
  {
    msg = ACTION_THIEVERY_STEAL_UNSUCCESSFUL_MONSTER;
  }

  msg = StringTable::get(msg);
  boost::replace_first(msg, "%s1", StringTable::get(steal_desc));
  boost::replace_first(msg, "%s2", StringTable::get(stealing_desc));
  msg[0] = toupper(msg[0]);

  return msg;
}

// Public
const string ActionTextKeys::ACTION_NOT_FOUND                  = "ACTION_NOT_FOUND";
const string ActionTextKeys::ACTION_SEARCH                     = "ACTION_SEARCH";
const string ActionTextKeys::ACTION_SEARCH_BLIND               = "ACTION_SEARCH_BLIND";
const string ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED        = "ACTION_PICK_UP_NOT_ALLOWED";
const string ActionTextKeys::ACTION_DROP_NOT_ALLOWED           = "ACTION_DROP_NOT_ALLOWED";
const string ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED      = "ACTION_DROP_NO_ITEM_SELECTED";
const string ActionTextKeys::ACTION_DROP_QUANTITY_PROMPT       = "ACTION_DROP_QUANTITY_PROMPT";
const string ActionTextKeys::ACTION_DROP_INVALID_QUANTITY      = "ACTION_DROP_INVALID_QUANTITY";
const string ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND  = "ACTION_PICK_UP_NOTHING_ON_GROUND";
const string ActionTextKeys::ACTION_PICK_UP_MAX_ITEMS          = "ACTION_PICK_UP_MAX_ITEMS";
const string ActionTextKeys::ACTION_MOVEMENT_BLOCKED           = "ACTION_MOVEMENT_BLOCKED";
const string ActionTextKeys::ACTION_PLAYER_DROWNING            = "ACTION_PLAYER_DROWNING";
const string ActionTextKeys::ACTION_PLAYER_FALLING             = "ACTION_PLAYER_FALLING";
const string ActionTextKeys::ACTION_PLAYER_OBLITERATED         = "ACTION_PLAYER_OBLITERATED";
const string ActionTextKeys::ACTION_PLAYER_FALL_FROM_MOUNTAIN  = "ACTION_PLAYER_FALL_FROM_MOUNTAIN";
const string ActionTextKeys::ACTION_PLAYER_STARVING_TO_DEATH   = "ACTION_PLAYER_STARVING_TO_DEATH";
const string ActionTextKeys::ACTION_DETECTED_HOSTILE_CREATURES = "ACTION_DETECTED_HOSTILE_CREATURES";
const string ActionTextKeys::ACTION_DETECTED_OUT_OF_DEPTH_CREATURES = "ACTION_DETECTED_OUT_OF_DEPTH_CREATURES";
const string ActionTextKeys::ACTION_LOOK                       = "ACTION_LOOK";
const string ActionTextKeys::ACTION_LOOK_UNEXPLORED_TILE       = "ACTION_LOOK_UNEXPLORED_TILE";
const string ActionTextKeys::ACTION_LOOK_TILE_OUT_OF_RANGE     = "ACTION_LOOK_TILE_OUT_OF_RANGE";
const string ActionTextKeys::ACTION_FIRE                       = "ACTION_FIRE";
const string ActionTextKeys::ACTION_NOTHING_HAPPENS            = "ACTION_NOTHING_HAPPENS";
const string ActionTextKeys::ACTION_CHAT_NOBODY_NEARBY         = "ACTION_CHAT_NOBODY_NEARBY";
const string ActionTextKeys::ACTION_CHAT_TIMEWALK              = "ACTION_CHAT_TIMEWALK";
const string ActionTextKeys::ACTION_CHAT_NO_RESPONSE           = "ACTION_CHAT_NO_RESPONSE";
const string ActionTextKeys::ACTION_GET_DIRECTION              = "ACTION_GET_DIRECTION";
const string ActionTextKeys::ACTION_GET_CARDINAL_DIRECTION     = "ACTION_GET_CARDINAL_DIRECTION";
const string ActionTextKeys::ACTION_OPEN_DOOR                  = "ACTION_OPEN_DOOR";
const string ActionTextKeys::ACTION_CLOSE_DOOR                 = "ACTION_CLOSE_DOOR";
const string ActionTextKeys::ACTION_OPEN_SARCOPHAGUS           = "ACTION_OPEN_SARCOPHAGUS";
const string ActionTextKeys::ACTION_OPEN_SARCOPHAGUS_CONFIRM   = "ACTION_OPEN_SARCOPHAGUS_CONFIRM";
const string ActionTextKeys::ACTION_OPEN_SARCOPHAGUS_ALREADY_OPEN = "ACTION_OPEN_SARCOPHAGUS_ALREADY_OPEN";
const string ActionTextKeys::ACTION_DOOR_DESTROYED             = "ACTION_DOOR_DESTROYED";
const string ActionTextKeys::ACTION_APPLY_NO_FEATURES_PRESENT  = "ACTION_APPLY_NO_FEATURES_PRESENT";
const string ActionTextKeys::ACTION_HANDLE_LOCK                = "ACTION_HANDLE_LOCK";
const string ActionTextKeys::ACTION_HANDLE_LOCK_NO_KEY         = "ACTION_HANDLE_LOCK_NO_KEY";
const string ActionTextKeys::ACTION_BESTIARY_WHICH_CREATURE    = "ACTION_BESTIARY_WHICH_CREATURE";
const string ActionTextKeys::ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS = "ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS";
const string ActionTextKeys::ACTION_POTION_EXPLODES            = "ACTION_POTION_EXPLODES";
const string ActionTextKeys::ACTION_AUTOMOVE_WORLD_MAP         = "ACTION_AUTOMOVE_WORLD_MAP";
const string ActionTextKeys::ACTION_AUTOMOVE_TOO_HUNGRY        = "ACTION_AUTOMOVE_TOO_HUNGRY";
const string ActionTextKeys::ACTION_AUTOMOVE_HOSTILE_CREATURES = "ACTION_AUTOMOVE_HOSTILE_CREATURES";
const string ActionTextKeys::ACTION_AUTOMOVE_BAD_STATUSES      = "ACTION_AUTOMOVE_BAD_STATUSES";
const string ActionTextKeys::ACTION_KICK_WORLD_MAP             = "ACTION_KICK_WORLD_MAP";
const string ActionTextKeys::ACTION_KICK_NOTHING_TO_KICK_AT    = "ACTION_KICK_NOTHING_TO_KICK_AT";
const string ActionTextKeys::ACTION_KICK_SOLID_TILE            = "ACTION_KICK_SOLID_TILE";
const string ActionTextKeys::ACTION_KICK_WATER_TILE            = "ACTION_KICK_WATER_TILE";
const string ActionTextKeys::ACTION_KICK_FORGE                 = "ACTION_KICK_FORGE";
const string ActionTextKeys::ACTION_KICK_JEWELER_WORKBENCH     = "ACTION_KICK_JEWELER_WORKBENCH";
const string ActionTextKeys::ACTION_KICK_TANNERY               = "ACTION_KICK_TANNERY";
const string ActionTextKeys::ACTION_KICK_WHEEL_AND_LOOM        = "ACTION_KICK_WHEEL_AND_LOOM";
const string ActionTextKeys::ACTION_KICK_BARREL                = "ACTION_KICK_BARREL";
const string ActionTextKeys::ACTION_KICK_SARCOPHAGUS           = "ACTION_KICK_SARCOPHAGUS";
const string ActionTextKeys::ACTION_KICK_TRAP                  = "ACTION_KICK_TRAP";
const string ActionTextKeys::ACTION_KICK_PASSES_THROUGH        = "ACTION_KICK_PASSES_THROUGH";
const string ActionTextKeys::ACTION_KICK_DOOR_DESTROYED        = "ACTION_KICK_DOOR_DESTROYED";
const string ActionTextKeys::ACTION_KICK_DOOR_BUCKLED          = "ACTION_KICK_DOOR_BUCKLED";
const string ActionTextKeys::ACTION_KICK_DOOR_UNMOVED          = "ACTION_KICK_DOOR_UNMOVED";
const string ActionTextKeys::ACTION_KICK_SPRAIN_LEG            = "ACTION_KICK_SPRAIN_LEG";
const string ActionTextKeys::ACTION_APPLY_TRAP_TOO_FAR         = "ACTION_APPLY_TRAP_TOO_FAR";
const string ActionTextKeys::ACTION_FORGE_NO_SUITABLE_HAMMER   = "ACTION_FORGE_NO_SUITABLE_HAMMER";
const string ActionTextKeys::ACTION_FORGE_NO_SMITHING_SKILL    = "ACTION_FORGE_NO_SMITHING_SKILL";
const string ActionTextKeys::ACTION_FORGE_NO_INGOTS            = "ACTION_FORGE_NO_INGOTS";
const string ActionTextKeys::ACTION_FORGE_ARTIFACT_SELECTED    = "ACTION_FORGE_ARTIFACT_SELECTED";
const string ActionTextKeys::ACTION_FORGE_FULL_POTENTIAL       = "ACTION_FORGE_FULL_POTENTIAL";
const string ActionTextKeys::ACTION_FORGE_SUCCESSFUL           = "ACTION_FORGE_SUCCESSFUL";
const string ActionTextKeys::ACTION_JEWELER_WORKBENCH_NO_JEWELER_SKILL = "ACTION_JEWELER_WORKBENCH_NO_JEWELER_SKILL";
const string ActionTextKeys::ACTION_SKIN_WORLD_MAP             = "ACTION_SKIN_WORLD_MAP";
const string ActionTextKeys::ACTION_SKIN_NO_CORPSES            = "ACTION_SKIN_NO_CORPSES";
const string ActionTextKeys::ACTION_SKIN_MANGLED_CORPSE        = "ACTION_SKIN_MANGLED_CORPSE";
const string ActionTextKeys::ACTION_SKIN_SUCCESSFUL            = "ACTION_SKIN_SUCCESSFUL";
const string ActionTextKeys::ACTION_SKIN_NO_SKINS              = "ACTION_SKIN_NO_SKINS";
const string ActionTextKeys::ACTION_SKIN_CREATE_ARMOUR         = "ACTION_SKIN_CREATE_ARMOUR";
const string ActionTextKeys::ACTION_WEAVE_NO_FIBRES            = "ACTION_WEAVE_NO_FIBRES";
const string ActionTextKeys::ACTION_WEAVE_NO_WEAVING_SKILL     = "ACTION_WEAVE_NO_WEAVING_SKILL";
const string ActionTextKeys::ACTION_WEAVE_SUCCESSFUL           = "ACTION_WEAVE_SUCCESSFUL";
const string ActionTextKeys::ACTION_SQUEEZE_FAILURE            = "ACTION_SQUEEZE_FAILURE";
const string ActionTextKeys::ACTION_DIG_AIR                    = "ACTION_DIG_AIR";
const string ActionTextKeys::ACTION_DIG_GROUND                 = "ACTION_DIG_GROUND";
const string ActionTextKeys::ACTION_DIG_WATER                  = "ACTION_DIG_WATER";
const string ActionTextKeys::ACTION_DIG_GRAVE                  = "ACTION_DIG_GRAVE";
const string ActionTextKeys::ACTION_DIG_UNDEAD_FOUND           = "ACTION_DIG_UNDEAD_FOUND";
const string ActionTextKeys::ACTION_DIG_ITEM_FOUND             = "ACTION_DIG_ITEM_FOUND";
const string ActionTextKeys::ACTION_DIG_THROUGH_TILE           = "ACTION_DIG_THROUGH_TILE";
const string ActionTextKeys::ACTION_DIG_CANNOT_DIG             = "ACTION_DIG_CANNOT_DIG";
const string ActionTextKeys::ACTION_DIG_CANNOT_DIG_ON_SUPER_TYPE = "ACTION_DIG_CANNOT_DIG_ON_SUPER_TYPE";
const string ActionTextKeys::ACTION_DIG_TOO_HARD               = "ACTION_DIG_TOO_HARD";
const string ActionTextKeys::ACTION_RESTING                    = "ACTION_RESTING";
const string ActionTextKeys::ACTION_HANDLE_DEFAULT             = "ACTION_HANDLE_DEFAULT";
const string ActionTextKeys::ACTION_HANDLE_ALTAR               = "ACTION_HANDLE_ALTAR";
const string ActionTextKeys::ACTION_HANDLE_PEW                 = "ACTION_HANDLE_PEW";
const string ActionTextKeys::ACTION_EVOKE_FAILED               = "ACTION_EVOKE_FAILED";
const string ActionTextKeys::ACTION_FISHING_NO_WATER           = "ACTION_FISHING_NO_WATER";
const string ActionTextKeys::ACTION_FISHING_NO_EQUIPMENT       = "ACTION_FISHING_NO_EQUIPMENT";
const string ActionTextKeys::ACTION_FISHING_BAIT1              = "ACTION_FISHING_BAIT1";
const string ActionTextKeys::ACTION_FISHING_BAIT2              = "ACTION_FISHING_BAIT2";
const string ActionTextKeys::ACTION_FISHING_BAIT3              = "ACTION_FISHING_BAIT3";
const string ActionTextKeys::ACTION_FISHING_NO_CATCH           = "ACTION_FISHING_NO_CATCH";
const string ActionTextKeys::ACTION_FISHING_ESCAPE             = "ACTION_FISHING_ESCAPE";
const string ActionTextKeys::ACTION_FISHING_NIBBLE             = "ACTION_FISHING_NIBBLE";
const string ActionTextKeys::ACTION_FISHING_CATCH              = "ACTION_FISHING_CATCH";
const string ActionTextKeys::ACTION_FISHING_THROW_BACK         = "ACTION_FISHING_THROW_BACK";
const string ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAPS      = "ACTION_DISARM_TRAPS_NO_TRAPS";
const string ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAP       = "ACTION_DISARM_TRAPS_NO_TRAP";
const string ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_DISMANTLE = "ACTION_DISARM_TRAPS_OUTCOME_DISMANTLE";
const string ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_DISARM = "ACTION_DISARM_TRAPS_OUTCOME_DISARM";
const string ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_FAIL  = "ACTION_DISARM_TRAPS_OUTCOME_FAIL";
const string ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_TRIGGER = "ACTION_DISARM_TRAPS_OUTCOME_TRIGGER";
const string ActionTextKeys::ACTION_THIEVERY_NO_TARGETS        = "ACTION_THIEVERY_NO_TARGETS";
const string ActionTextKeys::ACTION_THIEVERY_SELF_TARGET       = "ACTION_THIEVERY_SELF_TARGET";
const string ActionTextKeys::ACTION_THIEVERY_TOO_MANY_ITEMS    = "ACTION_THIEVERY_TOO_MANY_ITEMS";
const string ActionTextKeys::ACTION_INSCRIBE_WORLD_MAP         = "ACTION_INSCRIBE_WORLD_MAP";
const string ActionTextKeys::ACTION_INSCRIBE_WATER             = "ACTION_INSCRIBE_WATER";
const string ActionTextKeys::ACTION_INSCRIBE_AIR               = "ACTION_INSCRIBE_AIR";
const string ActionTextKeys::ACTION_INSCRIBE_GROUND            = "ACTION_INSCRIBE_GROUND";
const string ActionTextKeys::ACTION_INSCRIBE_QUERY             = "ACTION_INSCRIBE_QUERY";
const string ActionTextKeys::ACTION_POUR_EMPTY                 = "ACTION_POUR_EMPTY";
const string ActionTextKeys::ACTION_WANDCRAFT_INSUFFICIENT_COMPONENTS = "ACTION_WANDCRAFT_INSUFFICIENT_COMPONENTS";
const string ActionTextKeys::ACTION_WANDCRAFT_INSUFFICIENT_CASTINGS = "ACTION_WANDCRAFT_INSUFFICIENT_CASTINGS";
const string ActionTextKeys::ACTION_WANDCRAFT_NO_SPELLS        = "ACTION_WANDCRAFT_NO_SPELLS";
const string ActionTextKeys::ACTION_WANDCRAFT_WAND_CREATED     = "ACTION_WANDCRAFT_WAND_CREATED";
const string ActionTextKeys::ACTION_SCRIBING_INSUFFICIENT_COMPONENTS = "ACTION_SCRIBING_INSUFFICIENT_COMPONENTS";
const string ActionTextKeys::ACTION_SCRIBING_INSUFFICIENT_CASTINGS = "ACTION_SCRIBING_INSUFFICIENT_CASTINGS";
const string ActionTextKeys::ACTION_SCRIBING_NO_SPELLS         = "ACTION_SCRIBING_NO_SPELLS";
const string ActionTextKeys::ACTION_SCRIBING_SCROLL_CREATED    = "ACTION_SCRIBING_SCROLL_CREATED";

// Protected
const string ActionTextKeys::ACTION_EVOKE_PLAYER               = "ACTION_EVOKE_PLAYER";
const string ActionTextKeys::ACTION_EVOKE_MONSTER              = "ACTION_EVOKE_MONSTER";
const string ActionTextKeys::ACTION_QUAFF_PLAYER               = "ACTION_QUAFF_PLAYER";
const string ActionTextKeys::ACTION_QUAFF_MONSTER              = "ACTION_QUAFF_MONSTER";
const string ActionTextKeys::ACTION_EAT_PLAYER                 = "ACTION_EAT_PLAYER";
const string ActionTextKeys::ACTION_EAT_MONSTER                = "ACTION_EAT_MONSTER";
const string ActionTextKeys::ACTION_EAT_CONFIRMATION           = "ACTION_EAT_CONFIRMATION";
const string ActionTextKeys::ACTION_FULL_PLAYER                = "ACTION_FULL_PLAYER";
const string ActionTextKeys::ACTION_FULL_MONSTER               = "ACTION_FULL_MONSTER";
const string ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_PLAYER = "ACTION_SPELLCASTING_CANCELLED_PLAYER";
const string ActionTextKeys::ACTION_SPELLCASTING_CANCELLED_MONSTER = "ACTION_SPELLCASTING_CANCELLED_MONSTER";
const string ActionTextKeys::ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE = "ACTION_BESTIARY_PREVIOUS_SEARCH_MESSAGE";
const string ActionTextKeys::ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION = "ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION";
const string ActionTextKeys::ACTION_POUR_PLAYER                   = "ACTION_POUR_PLAYER";
const string ActionTextKeys::ACTION_POUR_MONSTER                  = "ACTION_POUR_MONSTER";
const string ActionTextKeys::ACTION_STUMBLE_PLAYER                = "ACTION_STUMBLE_PLAYER";
const string ActionTextKeys::ACTION_STUMBLE_MONSTER               = "ACTION_STUMBLE_MONSTER";
const string ActionTextKeys::ACTION_ALCOHOL_POISONING_PLAYER      = "ACTION_ALCOHOL_POISONING_PLAYER";
const string ActionTextKeys::ACTION_ALCOHOL_POISONING_MONSTER     = "ACTION_ALCOHOL_POISONING_MONSTER";
const string ActionTextKeys::ACTION_KICK_PLAYER                   = "ACTION_KICK_PLAYER";
const string ActionTextKeys::ACTION_KICK_MONSTER                  = "ACTION_KICK_MONSTER";
const string ActionTextKeys::ACTION_KNOCK_BACK_PLAYER             = "ACTION_KNOCK_BACK_PLAYER";
const string ActionTextKeys::ACTION_KNOCK_BACK_MONSTER            = "ACTION_KNOCK_BACK_MONSTER";
const string ActionTextKeys::ACTION_KICK_OBJECT_PLAYER            = "ACTION_KICK_OBJECT_PLAYER";
const string ActionTextKeys::ACTION_KICK_OBJECT_MONSTER           = "ACTION_KICK_OBJECT_MONSTER";
const string ActionTextKeys::ACTION_SPELL_WEAR_OFF_MONSTER        = "ACTION_SPELL_WEAR_OFF_MONSTER";
const string ActionTextKeys::ACTION_ITEM_BREAKAGE_PLAYER          = "ACTION_ITEM_BREAKAGE_PLAYER";
const string ActionTextKeys::ACTION_ITEM_BREAKAGE_MONSTER         = "ACTION_ITEM_BREAKAGE_MONSTER";
const string ActionTextKeys::ACTION_SPIT_OUT_SEED                 = "ACTION_SPIT_OUT_SEED";
const string ActionTextKeys::ACTION_SEED_PLANTED                  = "ACTION_SEED_PLANTED";
const string ActionTextKeys::ACTION_KEYBINDINGS                   = "ACTION_KEYBINDINGS";
const string ActionTextKeys::ACTION_INTRODUCTION_ROGUELIKES       = "ACTION_INTRODUCTION_ROGUELIKES";
const string ActionTextKeys::ACTION_SOTW_HISTORY                  = "ACTION_SOTW_HISTORY";
const string ActionTextKeys::ACTION_STRATEGY_BASICS               = "ACTION_STRATEGY_BASICS";
const string ActionTextKeys::ACTION_THIEVERY_ALREADY_STOLEN       = "ACTION_THIEVERY_ALREADY_STOLEN";
const string ActionTextKeys::ACTION_THIEVERY_NO_POCKETS           = "ACTION_THIEVERY_NO_POCKETS";
const string ActionTextKeys::ACTION_THIEVERY_STEAL_SUCCESSFUL_PLAYER = "ACTION_THIEVERY_STEAL_SUCCESSFUL_PLAYER";
const string ActionTextKeys::ACTION_THIEVERY_STEAL_SUCCESSFUL_MONSTER = "ACTION_THIEVERY_STEAL_SUCCESSFUL_MONSTER";
const string ActionTextKeys::ACTION_THIEVERY_STEAL_UNSUCCESSFUL_PLAYER = "ACTION_THIEVERY_STEAL_UNSUCCESSFUL_PLAYER";
const string ActionTextKeys::ACTION_THIEVERY_STEAL_UNSUCCESSFUL_MONSTER = "ACTION_THIEVERY_STEAL_UNSUCCESSFUL_MONSTER";

