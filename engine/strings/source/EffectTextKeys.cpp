#include <boost/algorithm/string/replace.hpp>
#include "EffectTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Strings for various magical effects
EffectTextKeys::EffectTextKeys()
{
}

EffectTextKeys::~EffectTextKeys()
{
}

string EffectTextKeys::get_healing_effect_message(const string& monster_desc_sid, const bool is_player)
{
  return get_general_effect_message(monster_desc_sid, is_player, EFFECT_HEALING_PLAYER, EFFECT_HEALING_MONSTER);
}

string EffectTextKeys::get_ether_effect_message(const string& monster_desc_sid, const bool is_player)
{
  return get_general_effect_message(monster_desc_sid, is_player, EFFECT_ETHER_PLAYER, EFFECT_ETHER_MONSTER);
}

string EffectTextKeys::get_teleport_effect_message(const string& monster_desc_sid, const bool is_player)
{
  return get_general_effect_message(monster_desc_sid, is_player, EFFECT_TELEPORT_PLAYER, EFFECT_TELEPORT_MONSTER);
}

string EffectTextKeys::get_general_effect_message(const string& monster_desc_sid, const bool is_player, const string& player_msg_sid, const string& monster_msg_sid)
{
  string message = StringTable::get(player_msg_sid);

  if (!is_player)
  {
    message = StringTable::get(monster_msg_sid);
    boost::replace_first(message, "%s", StringTable::get(monster_desc_sid));
    message[0] = toupper(message[0]);
  }
  
  return message;  
}

string EffectTextKeys::get_identify_individual_item_message(const string& unid_usage_desc_sid, const string& id_usage_desc_sid)
{
  string id_message = StringTable::get(EFFECT_IDENTIFY_ITEM);
  
  boost::replace_first(id_message, "%s", StringTable::get(unid_usage_desc_sid));
  boost::replace_first(id_message, "%s", StringTable::get(id_usage_desc_sid));
  
  return id_message;
}

string EffectTextKeys::get_wand_recharge_already_full_message(const string& wand_desc_sid)
{
  string recharge_msg = StringTable::get(EFFECT_RECHARGING_ALREADY_FULL);

  boost::replace_first(recharge_msg, "%s", StringTable::get(wand_desc_sid));

  return recharge_msg;
}

string EffectTextKeys::get_wand_recharge_message(const string& wand_desc_sid)
{
  string recharge_msg = StringTable::get(EFFECT_RECHARGING);

  boost::replace_first(recharge_msg, "%s", StringTable::get(wand_desc_sid));

  return recharge_msg;
}

const string EffectTextKeys::EFFECT_HEALING_PLAYER = "EFFECT_HEALING_PLAYER";
const string EffectTextKeys::EFFECT_HEALING_MONSTER = "EFFECT_HEALING_MONSTER";
const string EffectTextKeys::EFFECT_NULL = "EFFECT_NULL";
const string EffectTextKeys::EFFECT_SWEET_TASTE = "EFFECT_SWEET_TASTE";
const string EffectTextKeys::EFFECT_FRUIT_JUICE = "EFFECT_FRUIT_JUICE";
const string EffectTextKeys::EFFECT_IDENTIFY_ALL_ITEMS = "EFFECT_IDENTIFY_ALL_ITEMS";
const string EffectTextKeys::EFFECT_IDENTIFY_TYPE = "EFFECT_IDENTIFY_TYPE";
const string EffectTextKeys::EFFECT_IDENTIFY_ITEM = "EFFECT_IDENTIFY_ITEM";
const string EffectTextKeys::EFFECT_ETHER_PLAYER = "EFFECT_ETHER_PLAYER";
const string EffectTextKeys::EFFECT_ETHER_MONSTER = "EFFECT_ETHER_MONSTER";
const string EffectTextKeys::EFFECT_TELEPORT_PLAYER = "EFFECT_TELEPORT_PLAYER";
const string EffectTextKeys::EFFECT_TELEPORT_MONSTER = "EFFECT_TELEPORT_MONSTER";
const string EffectTextKeys::EFFECT_RECHARGING_PLAYER_NO_WANDS = "EFFECT_RECHARGING_PLAYER_NO_WANDS";
const string EffectTextKeys::EFFECT_RECHARGING = "EFFECT_RECHARGING";
const string EffectTextKeys::EFFECT_RECHARGING_ALREADY_FULL = "EFFECT_RECHARGING_ALREADY_FULL";
